#include "common.h"
#include "RCC.h"

inline void
APB2_clock_enable (uint32_t bit_position)
{    
    volatile uint32_t *apb2_reg = (uint32_t *) (RCC_BASE_ADDR + RCC_APB2ENR);
    BIT_SET(*apb2_reg, bit_position);
}