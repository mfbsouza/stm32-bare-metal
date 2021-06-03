# STM32F103xx "Blue Pill" Bare Metal Programing

Getting started with bare-metal programming on a STM32F103xx using Open Source GNU Toolchain

## Sections

- [Quick Start](#quick-start)
- [The Toolchain](#the-toolchain)
- [Contributing](#contributing)

## Quick Start

### 1. Get the files

    git clone https://github.com/mfbsouza/stm32-bare-metal.git

### 2. Write your code

write your code in `main.c` and create how many source files you want and compile it with:

    make

### 3. (Optional) Analyse it

check the `memory.map` file to check if everything is in other as expected, can also do:

    arm-none-eabi-objdump -h bin/firmware.elf

to check the final section headers

### 4. Flash it

put your STM32 in bootloader mode and just:

    make flash PORT=/dev/ttyUSB0

change `/dev/ttyUSB0` for the right port in your PC


## The Toolchain

- arm-none-eabi-gcc `(GNU C compiler for ARM)`
- arm-none-eabi-ld  `(GNU Linker for ARM)`
- arm-none-eabi-objcopy `(Convert GNU ELF files to bin & hex format)`
- GNU Make
- [STM32 Flash Programmer](https://sourceforge.net/projects/stm32flash/)

### Opcional:

- arm-none-eabi-objdump `(Verify ELF section headers and others)`

## Contributing

Please feel free to contribute to this project in anyway you may want (issues, pull request, ideas...). There is no template and anything will be welcome.