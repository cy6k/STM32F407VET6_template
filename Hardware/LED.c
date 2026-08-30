#include "stm32f4xx.h"
#include "LED.h"

/**
  * 函    数：LED初始化
  * 参    数：无
  * 返 回 值：无
  * 备    注：PA1、PA2，低电平点亮（与F103逻辑一致）
  */
void LED_Init(void)
{
    //开启时钟：F4 的 GPIO 挂在 AHB1 上，不再是 APB2！
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB, ENABLE);

    //GPIO初始化：F4 结构体拆成 Mode/OType/PuPd/Speed 四个独立成员
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin   = LED1_PIN | LED2_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;        // 输出模式
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;        // 推挽输出（对应 F1 的 Out_PP）
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;     // 不上拉不下拉（纯输出不需要）
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     // LED 用低速即可，2MHz 更省
    GPIO_Init(LED1_PORT, &GPIO_InitStructure);

    //设置初始化后的默认电平：高电平 = 灯灭（低电平点亮）
    GPIO_SetBits(LED1_PORT, LED1_PIN | LED2_PIN);
}

void LED1_ON(void)
{
    GPIO_ResetBits(LED1_PORT, LED1_PIN);
}

void LED1_OFF(void)
{
    GPIO_SetBits(LED1_PORT, LED1_PIN);
}

void LED1_Turn(void)
{
    if (GPIO_ReadOutputDataBit(LED1_PORT, LED1_PIN) == 0)
    {
        GPIO_SetBits(LED1_PORT, LED1_PIN);
    }
    else
    {
        GPIO_ResetBits(LED1_PORT, LED1_PIN);
    }
}

void LED2_ON(void)
{
    GPIO_ResetBits(LED2_PORT, LED2_PIN);
}

void LED2_OFF(void)
{
    GPIO_SetBits(LED2_PORT, LED2_PIN);
}

void LED2_Turn(void)
{
    if (GPIO_ReadOutputDataBit(LED2_PORT, LED2_PIN) == 0)
    {
        GPIO_SetBits(LED2_PORT, LED2_PIN);
    }
    else
    {
        GPIO_ResetBits(LED2_PORT, LED2_PIN);
    }
}
