/* Linker Script by Matheus Souza (github.com/mfbsouza) */

ENTRY (Reset_Handler)

MEMORY
{
    FLASH (RX) : ORIGIN = 0x08000000, LENGTH = 64K
    SRAM (RXW) : ORIGIN = 0x20000000, LENGTH = 20K
}

SECTIONS
{
    .text : {
        *(.isr_vector)
        *(.text)
        *(.rodata)
        . = ALIGN(4)
        _end_text =.;
    } >FLASH

    .data : {
        _start_data = .;
        *(.data)
        . = ALIGN(4)
        _end_data = .;
    }> SRAM AT> FLASH

    .bss : {
        _start_bss = .;
        *(.bss)
        . = ALIGN(4)
        _end_bss = .;
    }> SRAM
}