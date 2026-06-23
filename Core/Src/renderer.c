#include "renderer.h"
#include "obstacles.h"
#include <stdio.h>

void Renderer_Init(void)
{
    printf("\033[2J\033[H");
}

void Renderer_DrawMenu(uint32_t highScore)
{
    printf("\033[2J\033[H");
    printf("=====================================\n");
    printf("         STM32 PHYSICS GAME\n");
    printf("=====================================\n\n");
    printf("   Tilt the board to move the ball\n");
    printf("   Avoid obstacles and survive.\n\n");
    printf("   High Score: %lu\n\n", highScore);
    printf("   Press USER button to start\n");
}

void Renderer_DrawGame(const Body *ball,
                       const Obstacle *obsArr,
                       int score,
                       uint32_t highScore,
                       int gameOver,
                       const Particle *particles,
                       int particleCount)
{
    const int W = 40;
    const int H = 18;

    int bx = (int)((ball->pos.x + 1.0f) * (W / 2));
    int by = (int)((1.0f - ball->pos.y) * (H / 2));

    if (bx < 0) bx = 0;
    if (bx >= W) bx = W - 1;
    if (by < 0) by = 0;
    if (by >= H) by = H - 1;

    printf("\033[H");

    printf("Score: %d   High: %lu\n", score, highScore);
    if (gameOver)
        printf("GAME OVER! Press USER to restart.\n\n");
    else
        printf("\n");

    for (int j = 0; j < H; j++)
    {
        for (int i = 0; i < W; i++)
        {
            char c = ' ';

            if (j == 0 || j == H - 1)
                c = '-';
            else if (i == 0 || i == W - 1)
                c = '|';

            for (int k = 0; k < NUM_OBS; k++)
            {
                int ox1 = (int)((obsArr[k].x - obsArr[k].w/2 + 1.0f) * (W / 2));
                int ox2 = (int)((obsArr[k].x + obsArr[k].w/2 + 1.0f) * (W / 2));
                int oy1 = (int)((1.0f - (obsArr[k].y + obsArr[k].h/2)) * (H / 2));
                int oy2 = (int)((1.0f - (obsArr[k].y - obsArr[k].h/2)) * (H / 2));

                if (i >= ox1 && i <= ox2 && j >= oy1 && j <= oy2)
                    c = '#';
            }

            for (int p = 0; p < particleCount; p++)
            {
                if (!particles[p].active)
                    continue;

                int px = (int)((particles[p].pos.x + 1.0f) * (W / 2));
                int py = (int)((1.0f - particles[p].pos.y) * (H / 2));

                if (px == i && py == j)
                {
                    if (particles[p].life > 0.6f)      c = '*';
                    else if (particles[p].life > 0.3f) c = '+';
                    else                                c = '.';
                }
            }

            if (i == bx && j == by)
                c = 'o';

            printf("%c", c);
        }
        printf("\n");
    }
}

void Renderer_DrawGameOver(int score, uint32_t highScore, int newHighScore)
{
    printf("\033[2J\033[H");
    printf("============== GAME OVER ==============\n\n");
    printf("   Final Score: %d\n", score);
    printf("   High Score : %lu\n\n", highScore);
    if (newHighScore)
        printf("   NEW HIGH SCORE!\n\n");
    printf("   Press USER button to restart\n");
}
