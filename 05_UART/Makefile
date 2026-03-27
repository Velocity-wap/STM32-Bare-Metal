TARGET = main
BUILD_DIR = build

CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
OBJCOPY = arm-none-eabi-objcopy

CFLAGS = -mcpu=cortex-m3 -mthumb -nostdlib -nostartfiles -O0 -g
LDFLAGS = -T linker/stm32f103.ld -mcpu=cortex-m3 -mthumb -nostdlib

SRC = src/main.c
STARTUP = startup/startup_stm32f103.s

all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).bin

$(BUILD_DIR)/$(TARGET).elf: $(SRC) $(STARTUP)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) $(SRC) $(STARTUP) -o $@

$(BUILD_DIR)/$(TARGET).bin: $(BUILD_DIR)/$(TARGET).elf
	$(OBJCOPY) -O binary $< $@

flash:
	openocd -f interface/stlink-v2.cfg -f target/stm32f1x.cfg \
	-c "program $(BUILD_DIR)/$(TARGET).bin 0x08000000 verify reset exit"

clean:
	rm -rf $(BUILD_DIR)