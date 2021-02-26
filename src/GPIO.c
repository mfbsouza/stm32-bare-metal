#include "GPIO.h"

inline void
gpio_mode (gpio_pin_t pin, gpio_mode_t mode)
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

inline void
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

inline void
gpio_flip ( gpio_pin_t pin)
{
    volatile uint32_t *odr_reg = (uint32_t *) ( (PORT_BASE_ADDR + (0x400 * BYTE_HIGH(pin))) + (GPIO_ODR_OFFSET) );

    BIT_FLIP( *odr_reg, BYTE_LOW(pin) );
}

inline uint8_t
gpio_read ( gpio_pin_t pin)
{
    uint8_t buffer;
    volatile uint32_t *idr_reg = (uint32_t *) ( (PORT_BASE_ADDR + (0x400 * BYTE_HIGH(pin))) + (GPIO_IDR_OFFSET) );

    buffer = ( ((uint8_t)(*idr_reg >> BYTE_LOW(pin))) & 0x01 );
    return buffer;
}