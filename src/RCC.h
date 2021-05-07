/**
 * Reset & Clock control Library for STM32F103xx 
 * by Matheus Souza (github.com/mfbsouza)
 * 
 * this library has functions to help initialize clock for the peripherals
 * in the microcontroller
 * 
 * check page 47 of the reference manual for a overview how the components
 * are connect together.
 * 
 * 
 * APB2 Peripherals:
 *  
 *  | ADC1  | ADC2  | ADC3  | USART1 | SPI1  | TIM1  | TIM8  | EXTI |
 *  | GPIOA | GPIOB | GPIOC | GPIOD  | GPIOE | GPIOF | GPIOG | AFIO |
 * 
 * APB1 Periherals:
 *
 *  | DAC   | PWR   | BKP   | bxCAN  | USB   | I2C1  | I2C2  | RTC  |
 *  | TIM2  | TIM3  | TIM4  | USART3 | TIM5  | TIM6  | TIM7  | WWDG |
 *  | UART4 | UART5 | IWDG  | USART2 |   SPI3/I2C    |   SPI2/I2S   |
 * 
 */

#ifndef RCC_H_
#define RCC_H_

#include "common.h"

#define RCC_BASE_ADDR  0x40021000U

/* Offset Address */

#define RCC_APB2RSTR   0x0CU // APB2 peripheral reset register
#define RCC_APB1RSTR   0x10U // APB1 peripheral reset register
#define RCC_APB2ENR    0x18U // APB2 peripheral clock enable register
#define RCC_APB1ENR    0x1CU // APB1 peripheral clock enable register

/* Bit Positions */

typedef enum rcc_peripheral_t {
    GPIOA  = 0x02, // Port A clock enable bit position
    GPIOB  = 0x03, // Port B clock enable bit position
    GPIOC  = 0x04, // Port C clock enable bit position
    GPIOD  = 0x05, // Port D clock enable bit position
    GPIOE  = 0x06, // Port E clock enable bit position
    GPIOF  = 0x07, // Port F clock enable bit position
    GPIOG  = 0x08, // Port G clock enable bit position
    TIM1   = 0x0B, // TIM1 clock enable bit position
    USART1 = 0x0E  // USART1 clock enable bit position
} rcc_peripheral_t;

/* Functions */

static inline void
APB2_clock_enable ( rcc_peripheral_t peripheral )
{    
    volatile uint32_t *apb2_reg = (uint32_t *) (RCC_BASE_ADDR + RCC_APB2ENR);
    BIT_SET(*apb2_reg, peripheral);
}

#endif // RCC_H_