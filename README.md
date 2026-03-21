# STM32-Bare-Metal

## 01 - Bare Metal LED Blink
Blinks onboard LED on PC13 of STM32F103C8T6 (Blue Pill).

### What it does
- Enables GPIOC clock via RCC APB2ENR
- Configures PC13 as push-pull output via GPIOC CRH
- Toggles PC13 via GPIOC ODR in an infinite loop

### Registers used
- RCC APB2ENR (0x40021018) — enable GPIOC clock, bit 4
- GPIOC CRH (0x40011004) — configure PC13 as output
- GPIOC ODR (0x4001100C) — toggle PC13 HIGH/LOW
  
## 02 - Interrupts (WIP)
Button press on PA0 toggles onboard LED on PC13 of STM32F103C8T6 (Blue Pill).
Uses hardware interrupts — no polling.

### What it does
* Configures PA0 as floating input for button
* Configures PC13 as push-pull output for LED
* Triggers interrupt on falling edge (button press pulls PA0 LOW)
* ISR toggles PC13 and clears pending flag

### Registers used
* RCC APB2ENR (0x40021018) — enable GPIOA, GPIOC, AFIO clocks
* GPIOC CRH (0x40011004) — configure PC13 as push-pull output
* GPIOC ODR (0x4001100C) — toggle PC13
* GPIOA CRL (0x40010800) — configure PA0 as floating input
* AFIO EXTICR1 (0x40010008) — map PA0 to EXTI0
* EXTI IMR (0x40010400) — enable EXTI0 line
* EXTI FTSR (0x4001040C) — falling edge trigger on EXTI0
* EXTI PR (0x40010414) — clear pending flag in ISR
* NVIC_ISER0 (0xE000E100) — enable EXTI0 IRQ (bit 6)
* Software debounce delay in ISR to prevent multiple triggers per press

## 03 - I2C Bare Metal

I2C master write to SSD1306 OLED on STM32F103C8T6 (Blue Pill).

### What it does
* Configures PB6 (SCL) and PB7 (SDA) as alternate function open-drain
* Sets up I2C1 at 100kHz standard mode
* Generates START, sends slave address, sends dummy byte, generates STOP
* Pending hardware test — requires 4.7kΩ pull-up resistors on SCL and SDA

### Registers used
* RCC APB2ENR (0x40021018) — enable GPIOB clock
* RCC APB1ENR (0x4002101C) — enable I2C1 clock
* GPIOB CRL (0x40010800) — configure PB6, PB7 as alternate function open-drain
* I2C1 CR1 (0x40005000) — enable peripheral, generate START/STOP
* I2C1 CR2 (0x40005004) — set APB1 clock frequency (8MHz)
* I2C1 CCR (0x4000501C) — set I2C speed (100kHz)
* I2C1 TRISE (0x40005020) — set max rise time
* I2C1 DR (0x40005010) — send address and data bytes
* I2C1 SR1 (0x40005014) — check SB, ADDR, TXE flags
* I2C1 SR2 (0x40005018) — clear ADDR flag
  
## Toolchain
- Compiler: arm-none-eabi-gcc
- Build: make
- Flash: ST-Link V2 + OpenOCD
- Editor: VSCode

## No HAL, no libraries — direct register access only
