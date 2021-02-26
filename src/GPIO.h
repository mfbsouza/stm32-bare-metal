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

/* GPIO Parameters */

typedef enum {
    LOW,
    HIGH
} gpio_value_t;

typedef enum {
    OUTPUT_OPENDRAIN,
    OUTPUT_PUSHPULL
} gpio_mode_t;

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
gpio_mode ( gpio_pin_t pin, gpio_mode_t mode )
{
    uint8_t offset;
    volatile uint32_t *cr_reg;

    if (BYTE_LOW(pin) > 7) {
        offset = GPIO_CRH_OFFSET;
    }

    else {
        offset = GPIO_CRL_OFFSET;
    }
    
    cr_reg = (uint32_t *) ( (PORT_BASE_ADDR + (0x400 * BYTE_HIGH(pin))) + (offset) );

    if (mode == OUTPUT_OPENDRAIN) {
        *cr_reg |= ( (0x4U << ((BYTE_LOW(pin) % 8) * 4)) | (0x2U << ((BYTE_LOW(pin) % 8) * 4)) );
    }
}

static inline void
gpio_write (gpio_pin_t pin, gpio_value_t value)
{
    volatile uint32_t *odr_reg = (uint32_t *) ( (PORT_BASE_ADDR + (0x400 * BYTE_HIGH(pin))) + (GPIO_ODR_OFFSET) );
    
    if (value > 0 ) {
        BIT_SET( *odr_reg, BYTE_LOW(pin) );
    }
    else {
        BIT_CLR( *odr_reg, BYTE_LOW(pin) );
    }
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
#endif //GPIO_H_