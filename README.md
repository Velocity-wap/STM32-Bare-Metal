# 01 - Bare Metal LED Blink
Blinks onboard LED on PC13 of STM32F103C8T6 (Blue Pill).

## What it does
- Enables GPIOC clock via RCC APB2ENR
- Configures PC13 as push-pull output via GPIOC CRH
- Toggles PC13 via GPIOC ODR in an infinite loop

## Registers used
- RCC APB2ENR (0x40021018) — enable GPIOC clock, bit 4
- GPIOC CRH (0x40011004) — configure PC13 as output
- GPIOC ODR (0x4001100C) — toggle PC13 HIGH/LOW
  
# 02 - Interrupts (WIP)
Button press on PA0 toggles onboard LED on PC13 of STM32F103C8T6 (Blue Pill).
Uses hardware interrupts — no polling.

## What it does
* Configures PA0 as floating input for button
* Configures PC13 as push-pull output for LED
* Triggers interrupt on falling edge (button press pulls PA0 LOW)
* ISR toggles PC13 and clears pending flag

## Registers used
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
  
## No HAL, no libraries — direct register access only
