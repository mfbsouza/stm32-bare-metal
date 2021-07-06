TARGET = firmware

BUILD_DIR = build
BIN_DIR = bin
SRC_DIR = src

SRCS = $(shell find $(SRC_DIR) -name *.c)
OBJS = $(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%,$(SRCS:%=%.o))
DEPS = $(OBJS:.o=.d)

CC = arm-none-eabi-gcc
CFLAGS = -Wall -O0 -mcpu=cortex-m3 -mthumb -MMD -MP
LDFLAGS = -nostdlib -T stm32f103xx_ls.ld -Wl,-Map=memory.map

$(BIN_DIR)/$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# c source
$(BUILD_DIR)/%.c.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR) memory.map

.PHONY: flash
flash:
	stm32flash -w $(BIN_DIR)/$(TARGET).bin -v $(PORT)

.PHONY: objcopy
objcopy:
	arm-none-eabi-objcopy -O binary $(BIN_DIR)/$(TARGET) $(BIN_DIR)/$(TARGET).bin

-include $(DEPS)