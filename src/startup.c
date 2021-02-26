/**
 * startup code objectives:
 * 
 * 1. Create a vector table for the MCU based on the documentation
 * 2. Initializes .data and .bss section in the SRAM
 * 3. (Optional) init libc if using any
 * 4. Call main()
 */

#include "common.h"

/**
 * Defining the start of the Stack
 * 
 * ARM Cortex-M uses a descending stack, so the stack starts
 * at the end of the RAM and grows towards the beginning of the RAM
 */

#define SRAM_START   0x20000000U
#define SRAM_SIZE    (20 * 1024)
#define SRAM_END     ((SRAM_START) + (SRAM_SIZE))
#define STACK_START  SRAM_END

/**
 * Reset_Handler is the entry point defined in the Linker script
 * Reset_Handler will call main after initialization
 */

void Reset_Handler (void);
extern int main (void);

/* Functions prototype of STM32F103xx "Blue Pill" system exception and IRQ handlers */

void NMI_Handler                    (void) __attribute__ ((weak, alias("Default_Handler")));
void HardFault_Handler              (void) __attribute__ ((weak, alias("Default_Handler")));
void MemManage_Handler              (void) __attribute__ ((weak, alias("Default_Handler")));
void BusFault_Handler               (void) __attribute__ ((weak, alias("Default_Handler")));
void UsageFault_Handler             (void) __attribute__ ((weak, alias("Default_Handler")));
void SVC_Handler                    (void) __attribute__ ((weak, alias("Default_Handler")));
void DebugMon_Handler               (void) __attribute__ ((weak, alias("Default_Handler")));
void PendSV_Handler                 (void) __attribute__ ((weak, alias("Default_Handler")));
void SysTick_Handler                (void) __attribute__ ((weak, alias("Default_Handler")));
void WWDG_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void PVD_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
void TAMPER_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
void RTC_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
void FLASH_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void RCC_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI0_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI1_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI2_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI3_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI4_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel1_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel2_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel3_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel4_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel5_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel6_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel7_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void ADC1_2_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
void USB_HP_CAN_TX_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void USB_LP_CAN_RX0_IRQHandler      (void) __attribute__ ((weak, alias("Default_Handler")));
void CAN1_RX1_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void CAN1_SCE_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI9_5_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_BRK_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_UP_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_TRG_COM_IRQHandler        (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_CC_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM2_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM3_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM4_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C1_EV_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C1_ER_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C2_EV_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C2_ER_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void SPI1_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void SPI2_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void USART1_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
void USART2_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
void USART3_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI15_10_IRQHandler           (void) __attribute__ ((weak, alias("Default_Handler")));
void RTCAlarm_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void USBWakeup_IRQHandler           (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM8_BRK_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM8_UP_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM8_TRG_COM_IRQHandler        (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM8_CC_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void ADC3_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void FSMC_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void SDIO_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM5_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void SPI3_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void UART4_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void UART5_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM6_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM7_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Channel1_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Channel2_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Channel3_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Channel4_5_IRQHandler     (void) __attribute__ ((weak, alias("Default_Handler")));

/**
 * Creating the IVT or Vector Table and telling the compiler to
 * not put it in .data, instead put it in .isr_vector so later
 * the linker can copy it to the right address in the MCU memory.
 */

uint32_t *vector_table[] __attribute__((section(".isr_vector"))) = {
    (uint32_t *)STACK_START,
    (uint32_t *)Reset_Handler,
    (uint32_t *)NMI_Handler,
    (uint32_t *)HardFault_Handler,
    (uint32_t *)MemManage_Handler,
    (uint32_t *)BusFault_Handler,
    (uint32_t *)UsageFault_Handler,
    0,
    0,
    0,
    0,
    (uint32_t *)SVC_Handler,
    (uint32_t *)DebugMon_Handler,
    0,
    (uint32_t *)PendSV_Handler,
    (uint32_t *)SysTick_Handler,
    (uint32_t *)WWDG_IRQHandler,
    (uint32_t *)PVD_IRQHandler,
    (uint32_t *)TAMPER_IRQHandler,
    (uint32_t *)RTC_IRQHandler,
    (uint32_t *)FLASH_IRQHandler,
    (uint32_t *)RCC_IRQHandler,
    (uint32_t *)EXTI0_IRQHandler,
    (uint32_t *)EXTI1_IRQHandler,
    (uint32_t *)EXTI2_IRQHandler,
    (uint32_t *)EXTI3_IRQHandler,
    (uint32_t *)EXTI4_IRQHandler,
    (uint32_t *)DMA1_Channel1_IRQHandler,
    (uint32_t *)DMA1_Channel2_IRQHandler,
    (uint32_t *)DMA1_Channel3_IRQHandler,
    (uint32_t *)DMA1_Channel4_IRQHandler,
    (uint32_t *)DMA1_Channel5_IRQHandler,
    (uint32_t *)DMA1_Channel6_IRQHandler,
    (uint32_t *)DMA1_Channel7_IRQHandler,
    (uint32_t *)ADC1_2_IRQHandler,
    (uint32_t *)USB_HP_CAN_TX_IRQHandler,
    (uint32_t *)USB_LP_CAN_RX0_IRQHandler,
    (uint32_t *)CAN1_RX1_IRQHandler,
    (uint32_t *)CAN1_SCE_IRQHandler,
    (uint32_t *)EXTI9_5_IRQHandler,
    (uint32_t *)TIM1_BRK_IRQHandler,
    (uint32_t *)TIM1_UP_IRQHandler,
    (uint32_t *)TIM1_TRG_COM_IRQHandler,
    (uint32_t *)TIM1_CC_IRQHandler,
    (uint32_t *)TIM2_IRQHandler,
    (uint32_t *)TIM3_IRQHandler,
    (uint32_t *)TIM4_IRQHandler,
    (uint32_t *)I2C1_EV_IRQHandler,
    (uint32_t *)I2C1_ER_IRQHandler,
    (uint32_t *)I2C2_EV_IRQHandler,
    (uint32_t *)I2C2_ER_IRQHandler,
    (uint32_t *)SPI1_IRQHandler,
    (uint32_t *)SPI2_IRQHandler,
    (uint32_t *)USART1_IRQHandler,
    (uint32_t *)USART2_IRQHandler,
    (uint32_t *)USART3_IRQHandler,
    (uint32_t *)EXTI15_10_IRQHandler,
    (uint32_t *)RTCAlarm_IRQHandler,
    (uint32_t *)USBWakeup_IRQHandler,
    (uint32_t *)TIM8_BRK_IRQHandler,
    (uint32_t *)TIM8_UP_IRQHandler,
    (uint32_t *)TIM8_TRG_COM_IRQHandler,
    (uint32_t *)TIM8_CC_IRQHandler,
    (uint32_t *)ADC3_IRQHandler,
    (uint32_t *)FSMC_IRQHandler,
    (uint32_t *)SDIO_IRQHandler,
    (uint32_t *)TIM5_IRQHandler,
    (uint32_t *)SPI3_IRQHandler,
    (uint32_t *)UART4_IRQHandler,
    (uint32_t *)UART5_IRQHandler,
    (uint32_t *)TIM6_IRQHandler,
    (uint32_t *)TIM7_IRQHandler,
    (uint32_t *)DMA2_Channel1_IRQHandler,
    (uint32_t *)DMA2_Channel2_IRQHandler,
    (uint32_t *)DMA2_Channel3_IRQHandler,
    (uint32_t *)DMA2_Channel4_5_IRQHandler
};

__attribute__ ((noreturn))
void
Reset_Handler (void)
{
    // getting the symbol defined at the linker script contaning memory info

    extern uint32_t _end_text;
    extern uint32_t _start_data;
    extern uint32_t _end_data;
    extern uint32_t _start_bss;
    extern uint32_t _end_bss;

    // Copying .data section to SRAM

    uint32_t size = (uint32_t)&_end_data - (uint32_t)&_start_data;
    
    uint8_t *pDst = (uint8_t *)&_start_data; // SRAM
    uint8_t *pSrc = (uint8_t *)&_end_text;   // FLASH

    for (uint32_t byte_counter = 0; byte_counter < size; byte_counter++) {
        *pDst++ = *pSrc++;
    }

    // Initializing the .bss section to zero in the SRAM

    size = (uint32_t)&_end_bss - (uint32_t)&_start_bss;
    
    pDst = (uint8_t *)&_start_bss;

    for (uint32_t byte_counter = 0; byte_counter < size; byte_counter++) {
        *pDst++ = 0;
    }

    // (Optional) Initialize libc

    // Call main()
    main();

    // halt
    while(1);
}

void
Default_Handler (void)
{
    while(1); // halt
}