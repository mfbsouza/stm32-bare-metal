#ifndef TIMER_H_
#define TIMER_H_

#include "common.h"

/* Timer base memory address */

#define TIM2_BASE_ADDR 0x40000000
#define TIM3_BASE_ADDR 0x40000400
#define TIM4_BASE_ADDR 0x40000800

/* Offsets */

#define TIM_CR1_OFFSET  0x00
#define TIM_CR2_OFSSET  0x04
#define TIM_CNT_OFFSET  0x24
#define TIM_PSC_OFFSET  0x28


#endif // TIMER_H_