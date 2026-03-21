/**
 ******************************************************************************
 * 01_bare_metal_blink
 * Bare metal - zero HAL - direct register access
 * STM32F103C8T6
 ******************************************************************************
 */

#include <stdint.h>

int main(void)
{
	uint32_t *APB2ENR = (uint32_t *)(0x40021000 + 0x18);
	uint32_t *CRH = (uint32_t *)(0x40011000 + 0x04);
	uint32_t *ODR = (uint32_t *)(0x40011000 + 0x0C);
	*APB2ENR |= (1 << 4);
	*CRH &= ~(0xF << 20);
	*CRH |= (1<<20);
	 // for blinking we use PC13. CRH got cnf13(we need push-pull so 23:22 00) and mode13(we need 21:20 01 for 10mhz output)
	// First we made sure 20-23 are zero so we did *CRH & 0xf (shifted it to 20 then) and then made sure 20 is 1.
	while(1){
		*ODR &= ~(1<<13); //LED ON
		for(int i=0; i < 1000000; i++);
		*ODR |= (1<<13); //LED OFF
		for(int i=0; i <1000000; i++);
	}

}
