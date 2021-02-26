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

#include "common.h"

#define RCC_BASE_ADDR  0x40021000U

/* Offset Address */

#define RCC_APB2RSTR   0x0CU // APB2 peripheral reset register
#define RCC_APB1RSTR   0x10U // APB1 peripheral reset register
#define RCC_APB2ENR    0x18U // APB2 peripheral clock enable register
#define RCC_APB1ENR    0x1CU // APB1 peripheral clock enable register

/* Bit Positions */

#define IOPAEN     2U // Port A clock enable bit position
#define IOPBEN     3U // Port B clock enable bit position
#define IOPCEN     4U // Port C clock enable bit position
#define IOPDEN     5U // Port D clock enable bit position
#define IOPEEN     6U // Port E clock enable bit position
#define IOPFEN     7U // Port F clock enable bit position
#define IOPGEN     8U // Port G clock enable bit position
#define USART1EN  14U // USART1 clock enable bit position
#define TIM1EN    11U // TIM1 clock enable bit position

/* Functions */

void APB2_clock_enable (uint32_t bit_position);