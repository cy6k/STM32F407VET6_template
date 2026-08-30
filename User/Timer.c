/**
  ******************************************************************************
  * @file    Timer.c
  * @brief   非阻塞定时模块
  * @note    用 TIM6(基本定时器, APB1) 产生 1ms 中断;
  *          在 TIM6_DAC_IRQHandler 里调用各模块的 _Tick() 实现“状态机非阻塞”。
  *          GetTick() 用于在主循环中做非阻塞的“到时间就做”的判断。
  ******************************************************************************
  */
#include "Timer.h"
#include "stm32f4xx_tim.h"
#include "misc.h"

static volatile uint32_t g_ticks = 0;

void Timer_Init(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);

    /* APB1 定时器时钟 = 84MHz; PSC=83 -> 1MHz; ARR=999 -> 1000 次 = 1ms */
    TIM_TimeBaseStructure.TIM_Prescaler     = 83;
    TIM_TimeBaseStructure.TIM_Period        = 999;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);

    TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
    TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel                   = TIM6_DAC_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    TIM_Cmd(TIM6, ENABLE);
}

//TIM6每1ms中断
void TIM6_DAC_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM6, TIM_IT_Update) == SET)
    {
        TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
        g_ticks++;
    }
}

//获取毫秒计数(非阻塞)
uint32_t GetTick(void)
{
    return g_ticks;
}