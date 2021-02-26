/**
 * GPIO Library for STM32F103xx
 * by Matheus Souza (github.com/mfbsouza)
 * 
 */

#include "common.h"
#include "RCC.h"

/* GPIO PORT Memory Address */

#define PORT_BASE_ADDR  0x40010800U

/* GPIO offsets */

#define GPIO_CRL_OFFSET   0x00U // Port configuration low register
#define GPIO_CRH_OFFSET   0x04U // Port configuration high register
#define GPIO_IDR_OFFSET   0x08U // Port input data register
#define GPIO_ODR_OFFSET   0x0CU // Port output data register

/* GPIO Parameters */

#define LOW                 0x00
#define HIGH                0x01
#define OUTPUT_OPENDRAIN    0x07
#define OUTPUT_PUSHPULL     0x08

/* GPIO Pins */

#define PC10 0x2AU
#define PC11 0x2BU
#define PC12 0x2CU
#define PC13 0x2DU
#define PC14 0x2EU
#define PC15 0x2FU

/* Functions */

void    gpio_mode  ( uint8_t pin, uint8_t mode  );
void    gpio_write ( uint8_t pin, uint8_t value );
void    gpio_flip  ( uint8_t pin );
uint8_t gpio_read  ( uint8_t pin );