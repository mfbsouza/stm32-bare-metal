/**
 * Blink test code by Matheus Souza for the STM32F1xx
 */

#include <common/int_types.h>

#define RCC_ADDR         0x40021000U
#define RCC_CER_OFFSET   0x18U

#define PORTC_ADDR       0x40011000U

#define GPIO_CRL_OFFSET  0x00U
#define GPIO_CRH_OFFSET  0x04U
#define GPIO_ODR_OFFSET  0x0CU

int main (void)
{
    /* Enabling GPIO Clock for PORT C */
    volatile uint32_t *RCC_APB2ENR = (uint32_t *) (RCC_ADDR + RCC_CER_OFFSET);
    *RCC_APB2ENR |= (1 << 4);

    /* Configuring Port C pin 13 to Output Open-drain */
    volatile uint32_t *PORTC_CRH = (uint32_t *) (PORTC_ADDR + GPIO_CRH_OFFSET);
    *PORTC_CRH |= ( (0x4U << ((13 - 8) * 4)) | (0x2U << ((13 - 8) * 4)) ); // 0110b

    /* Port C Output data register */
    volatile uint32_t *PORTC_ODR = (uint32_t *) (PORTC_ADDR + GPIO_ODR_OFFSET);

    volatile uint32_t i;

    /* Main loop */
    while (1) {

        /* dump wait */
        for (i = 0; i < 100000; i++);

        /* toggle pin */
        *PORTC_ODR ^= (1 << 13);

    }

    return 0; // should not happen
}