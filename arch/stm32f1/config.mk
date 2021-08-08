# config related to STM32F1xx boards

PREFIX      := arm-none-eabi-
LDSCRIPT    := ./arch/stm32f1/linker_script.ld
STARTUPCODE := ./arch/stm32f1/startup.c
ARCHCFLAGS  := -mcpu=cortex-m3 -mthumb
ARCHLDFLAGS := -nostdlib -nostartfiles -T $(LDSCRIPT)

# Shared variable

ALLCSRCS  += \
	$(STARTUPCODE)

ALLCFLAGS += \
	$(ARCHCFLAGS)

ALLLDFLAGS += \
	$(ARCHLDFLAGS)
