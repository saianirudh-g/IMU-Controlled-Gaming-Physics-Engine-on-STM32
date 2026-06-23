#include "audio.h"
#include "tim.h"
#include "stm32f4xx_hal.h"

extern TIM_HandleTypeDef htim3;

static uint16_t s_freq = 0;
static uint16_t s_time = 0;
static uint32_t s_start = 0;

void Audio_Init(void)
{
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
}

void Audio_Play(uint16_t freq, uint16_t duration_ms)
{
    if (freq == 0 || duration_ms == 0)
    {
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
        s_time = 0;
        return;
    }

    s_freq  = freq;
    s_time  = duration_ms;
    s_start = HAL_GetTick();

    uint32_t period = (SystemCoreClock / freq) - 1;
    uint32_t pulse  = period / 2;

    __HAL_TIM_SET_AUTORELOAD(&htim3, period);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, pulse);
}

void Audio_Update(void)
{
    if (s_time == 0)
        return;

    if (HAL_GetTick() - s_start >= s_time)
    {
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
        s_time = 0;
    }
}
