/**
 * Startup code objectives:
 * 
 * 1. Create a vector table for the MCU based on the documentation
 * 2. Initializes .data and .bss section in the SRAM
 * 3. Call main()
 */


/**
 * Memory information about the MCU
 */

#define SRAM_START   0x20000000U
#define SRAM_SIZE    (20 * 1024)
#define SRAM_END     ((SRAM_START) + (SRAM_SIZE))
#define STACK_START  SRAM_END

/**
 * Functions prototype of STM32F103xx "Blue Pill" system exception and IRQ handlers
 */

void Reset_Handler (void);

void NMI_Handler                    (void) __attribute__ ((weak, alias("Default_Handler")));
void HardFault_Handler              (void) __attribute__ ((weak, alias("Default_Handler")));
void MemManage_Handler              (void) __attribute__ ((weak, alias("Default_Handler")));
void BusFault_Handler               (void) __attribute__ ((weak, alias("Default_Handler")));
void UsageFault_Handler             (void) __attribute__ ((weak, alias("Default_Handler")));
void SVC_Handler                    (void) __attribute__ ((weak, alias("Default_Handler")));
void DebugMon_Handler 				(void) __attribute__ ((weak, alias("Default_Handler")));
void PendSV_Handler   				(void) __attribute__ ((weak, alias("Default_Handler")));
void SysTick_Handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void WWDG_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));
void PVD_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));
void TAMPER_IRQHandler   			(void) __attribute__ ((weak, alias("Default_Handler")));
void RTC_IRQHandler        			(void) __attribute__ ((weak, alias("Default_Handler")));
void FLASH_IRQHandler      			(void) __attribute__ ((weak, alias("Default_Handler")));
void RCC_IRQHandler      			(void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI0_IRQHandler      			(void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI1_IRQHandler      			(void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI2_IRQHandler      			(void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI3_IRQHandler      			(void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI4_IRQHandler      			(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel1_IRQHandler      	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel2_IRQHandler      	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel3_IRQHandler      	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel4_IRQHandler      	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel5_IRQHandler      	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel6_IRQHandler      	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel7_IRQHandler      	(void) __attribute__ ((weak, alias("Default_Handler")));
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
void DMA2_Channel1_IRQHandler      	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Channel2_IRQHandler      	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Channel3_IRQHandler      	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Channel4_5_IRQHandler     (void) __attribute__ ((weak, alias("Default_Handler")));

/**
 * Creating the IVT or Vector Table and telling the compiler to
 * not put it in .data, instead put it in .isr_vector so later
 * the linker can copy it to the right address in the MCU memory.
 */

unsigned int vectors[] __attribute__((section(".isr_vector"))) = {
    STACK_START,
    (unsigned int)Reset_Handler,
    (unsigned int)NMI_Handler,
    (unsigned int)HardFault_Handler,
    (unsigned int)MemManage_Handler,
    (unsigned int)BusFault_Handler,
    (unsigned int)UsageFault_Handler,
    0,
    0,
    0,
    0,
    (unsigned int)SVC_Handler,
    (unsigned int)DebugMon_Handler,
    0,
    (unsigned int)PendSV_Handler,
    (unsigned int)SysTick_Handler,
    (unsigned int)WWDG_IRQHandler,
    (unsigned int)PVD_IRQHandler,
    (unsigned int)TAMPER_IRQHandler,
    (unsigned int)RTC_IRQHandler,
    (unsigned int)FLASH_IRQHandler,
    (unsigned int)RCC_IRQHandler,
    (unsigned int)EXTI0_IRQHandler,
    (unsigned int)EXTI1_IRQHandler,
    (unsigned int)EXTI2_IRQHandler,
    (unsigned int)EXTI3_IRQHandler,
    (unsigned int)EXTI4_IRQHandler,
    (unsigned int)DMA1_Channel1_IRQHandler,
    (unsigned int)DMA1_Channel2_IRQHandler,
    (unsigned int)DMA1_Channel3_IRQHandler,
    (unsigned int)DMA1_Channel4_IRQHandler,
    (unsigned int)DMA1_Channel5_IRQHandler,
    (unsigned int)DMA1_Channel6_IRQHandler,
    (unsigned int)DMA1_Channel7_IRQHandler,
    (unsigned int)ADC1_2_IRQHandler,
    (unsigned int)USB_HP_CAN_TX_IRQHandler,
    (unsigned int)USB_LP_CAN_RX0_IRQHandler,
    (unsigned int)CAN1_RX1_IRQHandler,
    (unsigned int)CAN1_SCE_IRQHandler,
    (unsigned int)EXTI9_5_IRQHandler,
    (unsigned int)TIM1_BRK_IRQHandler,
    (unsigned int)TIM1_UP_IRQHandler,
    (unsigned int)TIM1_TRG_COM_IRQHandler,
    (unsigned int)TIM1_CC_IRQHandler,
    (unsigned int)TIM2_IRQHandler,
    (unsigned int)TIM3_IRQHandler,
    (unsigned int)TIM4_IRQHandler,
    (unsigned int)I2C1_EV_IRQHandler,
    (unsigned int)I2C1_ER_IRQHandler,
    (unsigned int)I2C2_EV_IRQHandler,
    (unsigned int)I2C2_ER_IRQHandler,
    (unsigned int)SPI1_IRQHandler,
    (unsigned int)SPI2_IRQHandler,
    (unsigned int)USART1_IRQHandler,
    (unsigned int)USART2_IRQHandler,
    (unsigned int)USART3_IRQHandler,
    (unsigned int)EXTI15_10_IRQHandler,
    (unsigned int)RTCAlarm_IRQHandler,
    (unsigned int)USBWakeup_IRQHandler,
    (unsigned int)TIM8_BRK_IRQHandler,
    (unsigned int)TIM8_UP_IRQHandler,
    (unsigned int)TIM8_TRG_COM_IRQHandler,
    (unsigned int)TIM8_CC_IRQHandler,
    (unsigned int)ADC3_IRQHandler,
    (unsigned int)FSMC_IRQHandler,
    (unsigned int)SDIO_IRQHandler,
    (unsigned int)TIM5_IRQHandler,
    (unsigned int)SPI3_IRQHandler,
    (unsigned int)UART4_IRQHandler,
    (unsigned int)UART5_IRQHandler,
    (unsigned int)TIM6_IRQHandler,
    (unsigned int)TIM7_IRQHandler,
    (unsigned int)DMA2_Channel1_IRQHandler,
    (unsigned int)DMA2_Channel2_IRQHandler,
    (unsigned int)DMA2_Channel3_IRQHandler,
    (unsigned int)DMA2_Channel4_5_IRQHandler
};

void
Default_Handler (void)
{
    while(1); // just hangs
}

void
Reset_Handler (void)
{
    // Copy .data section to SRAM

    // Init the .bss section to zero in SRAM

    // Call main()
}