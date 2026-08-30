/**
  ******************************************************************************
  * @file    main.c
  * @brief   Main program body (非阻塞模板)
  * @note    Clock: 168MHz @ 8MHz HSE (SystemInit). HSE_VALUE=8M, PLL_M=8.
  *          Timing: 用 Timer(TIM6) 的非阻塞 GetTick(), 不要用阻塞 Delay。
  ******************************************************************************
  */
#include "main.h"
#include "Timer.h"
#include "LED.h"

int main(void)
{
  /* System clock is already configured by SystemInit() (168MHz, 8MHz HSE).
     Do NOT reconfigure the RCC/PLL here. */

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	//本工程的中断优先级按 2 位抢占 + 2 位子优先级来解读 

    Timer_Init();   //启动 1ms 定时器 -> GetTick() 非阻塞计时
	LED_Init();

	static uint32_t last = 0;   //记录上次执行的时间点(static 保证循环间不变)

  /* ---- Add your application init here ---- */

	while (1)
	{
	  //非阻塞:每 500ms 做一次，不卡住主循环
		if (GetTick() - last >= 500)
		{
		last = GetTick();
		//在这里写每 500ms 要做的事
			LED1_Turn();
			LED2_Turn();
		}

    //其它非阻塞任务也放这里（不会互相卡住）
	}
}
