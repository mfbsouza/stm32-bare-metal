/**
 * GPIO Library for STM32F103xx
 * by Matheus Souza (github.com/mfbsouza)
 * 
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <common/int_types.h>

/* GPIO PORT Memory Address */

#define PORT_BASE_ADDR  0x40010800U

/* GPIO offsets */

#define GPIO_CRL_OFFSET   0x00U // Port configuration low register
#define GPIO_CRH_OFFSET   0x04U // Port configuration high register
#define GPIO_IDR_OFFSET   0x08U // Port input data register
#define GPIO_ODR_OFFSET   0x0CU // Port output data register

/* GPIO Macro functions */

#define GET_CR_OFFSET(PIN)  ( (PIN > 7) ? GPIO_CRH_OFFSET : GPIO_CRL_OFFSET )

/* GPIO data types */

typedef enum gpio_value_t {
    LOW,
    HIGH
} gpio_value_t;

typedef enum gpio_mode_t {
    OUTPUT_PUSHPULL  = 0x00,
    OUTPUT_OPENDRAIN = 0x01,
    ANALOG           = 0x00,
    INPUT            = 0x01,
    INPUT_PULLDOWN   = 0x02,
    INPUT_PULLUP     = 0x12
} gpio_mode_t;

typedef enum gpio_speed_t {
    NOT_DEFINED,
    OUTPUT_10MHZ,
    OUTPUT_2MHZ,
    OUTPUT_50MHZ
} gpio_speed_t;

/* GPIO Pins */

typedef enum gpio_pin_t {
    PC10 = 0x2A,
    PC11 = 0x2B,
    PC12 = 0x2C,
    PC13 = 0x2D,
    PC14 = 0x2E,
    PC15 = 0x2F
} gpio_pin_t;

/**
 * Function: gpio_mode
 * 
 * Parameters: gpio pin | gpio mode | gpio speed
 * 
 * gpio_mode configures two registers (GPIOx_CR and GPIOx_ODR)
 * according to the parameters
 */

static inline void
gpio_mode ( gpio_pin_t pin, gpio_mode_t mode, gpio_speed_t speed )
{
    volatile uint32_t *cr_reg, *odr_reg;
    
    // CR REG ADDRESS = GPIO_PORT_BASE_ADDR + PORT_x_OFFSET + CRH OR CRL OFFSET
    cr_reg = (uint32_t *) ( PORT_BASE_ADDR + (BYTE_HIGH(pin) << 10) + (GET_CR_OFFSET(BYTE_LOW(pin))) );
    
    // ODR REG ADDRESS = GPIO_PORT_BASE_ADDR + PORT_x_OFFSET + ODR OFFSET
    odr_reg = (uint32_t *) ( PORT_BASE_ADDR + (BYTE_HIGH(pin) << 10) + GPIO_ODR_OFFSET );
    
    // Set CNF[1:0], MODE[1:0] and PxODR according to the table 21 and 20 in the datasheet
    REG_UPDATE( *cr_reg , BYTE_LOW(mode)  , TWOBITS, (((BYTE_LOW(pin) & 0x07) << 2) + 2) );
    REG_UPDATE( *cr_reg , speed           , TWOBITS, ((BYTE_LOW(pin) & 0x07) << 2) );
    REG_UPDATE( *odr_reg, BYTE_HIGH(mode) , ONEBIT , BYTE_LOW(pin) );
}

/**
 * Function: gpio_write
 * 
 * Parameters: gpio pin | gpio value
 * 
 * gpio_write takes a gpio value (high or low) and sets
 * the gpio pin with that value
 */

static inline void
gpio_write ( gpio_pin_t pin, gpio_value_t value )
{
    volatile uint32_t *odr_reg;
    
    // ODR REG ADDRESS = GPIO_PORT_BASE_ADDR + PORT_x_OFFSET + ODR OFFSET
    odr_reg = (uint32_t *) ( PORT_BASE_ADDR + (BYTE_HIGH(pin) << 10) + GPIO_ODR_OFFSET );

    REG_UPDATE(*odr_reg, value, ONEBIT, BYTE_LOW(pin));
}

/**
 * Function: gpio_flip
 * 
 * Parameters: gpio pin
 * 
 * gpio_flip inverts the output value of a given pin
 */

static inline void
gpio_flip ( gpio_pin_t pin )
{
    volatile uint32_t *odr_reg;
    
    // ODR REG ADDRESS = GPIO_PORT_BASE_ADDR + PORT_x_OFFSET + ODR OFFSET
    odr_reg = (uint32_t *) ( PORT_BASE_ADDR + (BYTE_HIGH(pin) << 10) + GPIO_ODR_OFFSET );

    BIT_FLIP( *odr_reg, BYTE_LOW(pin) );
}

/**
 * Fcuntion: gpio_read
 * 
 * Parameters: gpio pin
 * 
 * gpio_read returns the gpio value of a given pin
 */

static inline gpio_value_t
gpio_read ( gpio_pin_t pin)
{
    gpio_value_t buffer;
    volatile uint32_t *idr_reg;
    
    // IDR REG ADDRESS = GPIO_PORT_BASE_ADDR + PORT_x_OFFSET + ODR OFFSET
    idr_reg = (uint32_t *) ( PORT_BASE_ADDR + (BYTE_HIGH(pin) << 10) + GPIO_IDR_OFFSET );

    buffer = (gpio_value_t) ((*idr_reg >> BYTE_LOW(pin)) & 0x01);
    return buffer;
}

#endif // GPIO_H_
