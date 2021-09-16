# Makefile by Matheus Souza (github.com/mfbsouza)
# based on ChibiOS's Build System

# project name

PROJECT  := firmware

# paths

BUILDDIR := ./build
OBJDIR   := $(BUILDDIR)/obj
BINDIR   := $(BUILDDIR)/bin

# board configuration and startup code

include ./arch/stm32f1/config.mk

# sources to compile

include ./kernel/sources.mk

# compiler settings

CC  := $(PREFIX)gcc
AS  := $(PREFIX)gcc
LD  := $(PREFIX)gcc
CP  := $(PREFIX)objcopy
OD  := $(PREFIX)objdump
HEX := $(CP) -O ihex
BIN := $(CP) -O binary

CFLAGS   := -std=c99 -Wall -O0 $(ALLCFLAGS) -MMD -MP
LDFLAGS  := $(ALLLDFLAGS)

# sources

CSRCS    := $(ALLCSRCS)
ASMSRCS  := $(ALLASMSRCS)
SRCPATHS := $(sort $(dir $(CSRCS)) $(dir $(ASMSRCS)))

# objects

COBJS   := $(addprefix $(OBJDIR)/, $(notdir $(CSRCS:.c=.o)))
ASMOBJS := $(addprefix $(OBJDIR)/, $(notdir $(ASMOBJS:.s=.o)))
OBJS    := $(COBJS) $(ASMOBJS)
DEPS    := $(OBJS:.o=.d)

# paths where to search for sources

VPATH   = $(SRCPATHS)

# output

OUTFILES := \
	$(BINDIR)/$(PROJECT).elf \
	$(BINDIR)/$(PROJECT).hex \
	$(BINDIR)/$(PROJECT).bin

# targets

all: $(OBJDIR) $(BINDIR) $(OBJS) $(OUTFILES)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(BINDIR):
	@mkdir -p $(BINDIR)

# target for c objects

$(COBJS) : $(OBJDIR)/%.o : %.c
ifeq ($(VERBOSE),1)
	$(CC) -c $(CFLAGS) -I. $< -o $@
else
	@echo CC $<
	@$(CC) -c $(CFLAGS) -I. $< -o $@
endif

# target for asm objects

$(ASMOBJS) : $(OBJDIR)/%.o : %.s
ifeq ($(VERBOSE),1)
	$(AS) -c $(CFLAGS) $< -o $@
else
	@echo AS $<
	@$(AS) -c $(CFLAGS) $< -o $@
endif

# target for ELF file

$(BINDIR)/$(PROJECT).elf: $(OBJS)
ifeq ($(VERBOSE),1)
	$(LD) $(LDFLAGS) $(OBJS) -o $@
else
	@echo LD ./$@
	@$(LD) $(LDFLAGS) $(OBJS) -o $@
endif

%.hex: %.elf
ifeq ($(VERBOSE),1)
	$(HEX) $< $@
else
	@echo HEX $@
	@$(HEX) $< $@
endif

%.bin: %.elf
ifeq ($(VERBOSE),1)
	$(BIN) $< $@
else
	@echo BIN $@
	@$(BIN) $< $@
endif

clean:
	rm -rf $(BUILDDIR)

# Include the dependency files, should be the last of the makefile

-include $(DEPS)
