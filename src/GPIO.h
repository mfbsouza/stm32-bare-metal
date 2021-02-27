/**
 * GPIO Library for STM32F103xx
 * by Matheus Souza (github.com/mfbsouza)
 * 
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "common.h"

/* GPIO PORT Memory Address */

#define PORT_BASE_ADDR  0x40010800U

/* GPIO offsets */

#define GPIO_CRL_OFFSET   0x00U // Port configuration low register
#define GPIO_CRH_OFFSET   0x04U // Port configuration high register
#define GPIO_IDR_OFFSET   0x08U // Port input data register
#define GPIO_ODR_OFFSET   0x0CU // Port output data register

/* GPIO Macro functions */

#define GET_OFFSET(PIN)  ( (PIN > 7) ? GPIO_CRH_OFFSET : GPIO_CRL_OFFSET )

/* GPIO Parameters */

typedef enum {
    LOW,
    HIGH
} gpio_value_t;

typedef enum {
    OUTPUT_PUSHPULL  = 0x00,
    OUTPUT_OPENDRAIN = 0x01,
    ANALOG           = 0x00,
    INPUT            = 0x01,
    INPUT_PULLDOWN   = 0x02,
    INPUT_PULLUP     = 0x12
} gpio_mode_t;

typedef enum {
    NOT_DEFINED,
    OUTPUT_10MHZ,
    OUTPUT_2MHZ,
    OUTPUT_50MHZ
} gpio_speed_t;

/* GPIO Pins */

typedef enum {
    PC10 = 0x2A,
    PC11 = 0x2B,
    PC12 = 0x2C,
    PC13 = 0x2D,
    PC14 = 0x2E,
    PC15 = 0x2F
} gpio_pin_t;

/* Functions */

static inline void
gpio_mode ( gpio_pin_t pin, gpio_mode_t mode, gpio_speed_t speed )
{
    volatile uint32_t *cr_reg, *odr_reg;
    
    cr_reg = (uint32_t *) ( (PORT_BASE_ADDR + (0x400 * BYTE_HIGH(pin))) + (GET_OFFSET(BYTE_LOW(pin))) );
    odr_reg = (uint32_t *) ( (PORT_BASE_ADDR + (0x400 * BYTE_HIGH(pin))) + (GPIO_ODR_OFFSET) );
    
    // SET CNF[1:0] , MODE[1:0] and PxODR
    REG_UPDATE(*cr_reg, (uint32_t)(mode & 0x0F), (uint32_t)0x3, (((BYTE_LOW(pin) % 8) * 4) + 2));
    REG_UPDATE(*cr_reg, (uint32_t)speed, (uint32_t)0x3, ((BYTE_LOW(pin) % 8) * 4));
    REG_UPDATE(*odr_reg, (uint32_t)((mode & 0xF0) >> 4), (uint32_t)0x1, BYTE_LOW(pin));
}

static inline void
gpio_write (gpio_pin_t pin, gpio_value_t value)
{
    volatile uint32_t *odr_reg = (uint32_t *) ( (PORT_BASE_ADDR + (0x400 * BYTE_HIGH(pin))) + (GPIO_ODR_OFFSET) );
    REG_UPDATE(*odr_reg, (uint32_t)value, (uint32_t)0x1, BYTE_LOW(pin));
}

static inline void
gpio_flip ( gpio_pin_t pin)
{
    volatile uint32_t *odr_reg = (uint32_t *) ( (PORT_BASE_ADDR + (0x400 * BYTE_HIGH(pin))) + (GPIO_ODR_OFFSET) );
    BIT_FLIP( *odr_reg, BYTE_LOW(pin) );
}

static inline uint8_t
gpio_read ( gpio_pin_t pin)
{
    uint8_t buffer;
    volatile uint32_t *idr_reg = (uint32_t *) ( (PORT_BASE_ADDR + (0x400 * BYTE_HIGH(pin))) + (GPIO_IDR_OFFSET) );

    buffer = ( ((uint8_t)(*idr_reg >> BYTE_LOW(pin))) & 0x01 );
    return buffer;
}

#endif // GPIO_H_