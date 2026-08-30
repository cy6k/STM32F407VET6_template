#ifndef __LED_H
#define __LED_H

#include "stm32f4xx.h"

/* LED pin mapping: edit here for other boards */
#define LED1_PORT   GPIOA
#define LED1_PIN    GPIO_Pin_1
#define LED2_PORT   GPIOA
#define LED2_PIN    GPIO_Pin_2

void LED_Init(void);
void LED1_ON(void);
void LED1_OFF(void);
void LED1_Turn(void);
void LED2_ON(void);
void LED2_OFF(void);
void LED2_Turn(void);

#endif

