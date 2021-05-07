#include "common.h"
#include "RCC.h"
#include "GPIO.h"

int main (void)
{
    int i;

    APB2_clock_enable(GPIOC);
    gpio_mode(PC13, OUTPUT_OPENDRAIN, OUTPUT_2MHZ);

    while(1) {

        for(i = 0; i < 1000000; i++);

        gpio_flip(PC13);
    }

    return 0; // should not happen
}