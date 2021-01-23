# Makefile by Matheus Souza (github.com/mfbsouza)

# Project name

NAME = firmware

# Directory sctructure

SRCDIR = src
BUILDDIR = build
BINDIR = bin
SRCEXT = c
SOURCES = $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS = $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

# Compiler & Linker settings

# https://gcc.gnu.org/onlinedocs/gcc-10.2.0/gcc/ARM-Options.html#ARM-Options
CC = arm-none-eabi-gcc
CFLAGS = -Wall -O0 -mcpu=cortex-m3 -mthumb
LDFLAGS = -nostdlib -T stm32f103xx_ls.ld -Wl,-Map=memory.map

all: $(BINDIR)/$(NAME).bin $(BINDIR)/$(NAME).hex

$(BINDIR)/$(NAME).bin: $(BINDIR)/$(NAME).elf
	arm-none-eabi-objcopy -O binary $< $@

$(BINDIR)/$(NAME).hex: $(BINDIR)/$(NAME).elf
	arm-none-eabi-objcopy -O ihex $< $@

$(BINDIR)/$(NAME).elf: $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) $(LDFLAGS) $^ -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	rm -rf $(BUILDDIR) $(BINDIR) memory.map

flash:
	stm32flash -w $(BINDIR)/$(NAME).bin -v $(PORT)

.PHONY: all clean flash