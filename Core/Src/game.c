#include "game.h"
#include "renderer.h"
#include "particles.h"
#include "obstacles.h"
#include "audio.h"
#include "mpu6050.h"
#include "gpio.h"
#include "stm32f4xx_hal.h"
#include <math.h>

#define FLASH_SECTOR_11_ADDR 0x080E0000

extern I2C_HandleTypeDef hi2c1;

GameState g_gameState = GAME_STATE_MENU;

static Body     s_ball;
static int      s_score        = 0;
static int      s_gameOver     = 0;
static int      s_newHighScore = 0;
static uint32_t s_highScore    = 0;
static float    s_obstacleSpeed = 0.4f;

static float s_smoothPitch = 0.0f;
static float s_smoothRoll  = 0.0f;

static uint32_t Flash_ReadHighScore(void)
{
    uint32_t value = *(uint32_t*)FLASH_SECTOR_11_ADDR;
    if (value == 0xFFFFFFFF)
        return 0;
    return value;
}

static void Flash_WriteHighScore(uint32_t score)
{
    HAL_FLASH_Unlock();

    FLASH_EraseInitTypeDef erase;
    uint32_t sectorError = 0;

    erase.TypeErase    = FLASH_TYPEERASE_SECTORS;
    erase.Sector       = FLASH_SECTOR_11;
    erase.NbSectors    = 1;
    erase.VoltageRange = FLASH_VOLTAGE_RANGE_3;

    HAL_FLASHEx_Erase(&erase, &sectorError);
    HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, FLASH_SECTOR_11_ADDR, score);

    HAL_FLASH_Lock();
}

static int ButtonPressed(void)
{
    return HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET;
}

static void IMU_GetTiltAngles(MPU6050_Data *imu, float *pitch, float *roll)
{
    *pitch = atanf(imu->ay / imu->az);
    *roll  = atanf(-imu->ax / imu->az);
}

static void ResetGame(void)
{
    s_ball.pos.x = 0.0f;
    s_ball.pos.y = 0.0f;
    s_ball.vel.x = 0.0f;
    s_ball.vel.y = 0.0f;
    s_ball.acc.x = 0.0f;
    s_ball.acc.y = -9.8f;

    s_score        = 0;
    s_gameOver     = 0;
    s_newHighScore = 0;
    s_obstacleSpeed = 0.4f;

    s_smoothPitch = 0.0f;
    s_smoothRoll  = 0.0f;

    Obstacles_Init();
    Particles_Init();
}

void Game_Init(void)
{
    s_highScore = Flash_ReadHighScore();
    ResetGame();
    Renderer_Init();
}

void Game_Update(float dt)
{
    static MPU6050_Data imu;

    Audio_Update();

    switch (g_gameState)
    {
        case GAME_STATE_MENU:
            Renderer_DrawMenu(s_highScore);
            if (ButtonPressed())
            {
                HAL_Delay(200);
                ResetGame();
                g_gameState = GAME_STATE_PLAYING;
            }
            break;

        case GAME_STATE_PLAYING:
        {
            MPU6050_Read(&hi2c1, &imu);

            float pitch, roll;
            IMU_GetTiltAngles(&imu, &pitch, &roll);

            s_smoothPitch = 0.9f * s_smoothPitch + 0.1f * pitch;
            s_smoothRoll  = 0.9f * s_smoothRoll  + 0.1f * roll;

            float gain = 4.0f;
            s_ball.acc.x = s_smoothRoll  * gain;
            s_ball.acc.y = s_smoothPitch * gain;

            if (s_ball.acc.x > 10.0f)  s_ball.acc.x = 10.0f;
            if (s_ball.acc.x < -10.0f) s_ball.acc.x = -10.0f;
            if (s_ball.acc.y > 10.0f)  s_ball.acc.y = 10.0f;
            if (s_ball.acc.y < -10.0f) s_ball.acc.y = -10.0f;

            Physics_Update(&s_ball, dt);

            s_obstacleSpeed = 0.4f + (s_score * 0.0005f);
            Obstacles_Update(dt, s_obstacleSpeed);

            Particles_SpawnDust(s_ball.pos.x, s_ball.pos.y);
            Particles_Update(dt);

            if (Obstacles_CheckCollision(&s_ball))
            {
                s_gameOver = 1;
            }

            if (!s_gameOver)
            {
                s_score++;
                if (s_score % 500 == 0)
                    Audio_Play(1200, 80);
            }
            else
            {
                if (s_score > s_highScore)
                {
                    s_highScore = s_score;
                    Flash_WriteHighScore(s_highScore);
                    s_newHighScore = 1;
                }
                Particles_SpawnExplosion(s_ball.pos.x, s_ball.pos.y);
                Audio_Play(150, 300);
                g_gameState = GAME_STATE_GAMEOVER;
            }

            Renderer_DrawGame(&s_ball,
                              g_obstacles,
                              s_score,
                              s_highScore,
                              s_gameOver,
                              g_particles,
                              MAX_PARTICLES);
        }
        break;

        case GAME_STATE_GAMEOVER:
            Renderer_DrawGameOver(s_score, s_highScore, s_newHighScore);
            if (ButtonPressed())
            {
                HAL_Delay(200);
                ResetGame();
                g_gameState = GAME_STATE_PLAYING;
            }
            break;
    }
}
