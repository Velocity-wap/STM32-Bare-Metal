/*
 * 02_interrupts: Button on PA0 toggles LED on PC13
 * Bare metal - zero HAL - direct register access
 * STM32F103C8T6
 */

#include <stdint.h>
uint32_t *ODR = (uint32_t *)(0x40011000 + 0x0C);
uint32_t *PR = (uint32_t *)(0x40010400 + 0x14);//clear pending interrupt flag inside instruction service routine

int main(void)
{
	uint32_t *APB2ENR = (uint32_t *)(0x40021000 + 0x18);
	uint32_t *CRH = (uint32_t *)(0x40011000 + 0x04);//configure pc13 as output
	uint32_t *CRL = (uint32_t *)(0x40010800 + 0x00);//configure pc13 when button pressed
	uint32_t *EXTICR1 = (uint32_t *)(0x40010000 + 0x08);//connects PA0 to EXTI0
	uint32_t *IMR = (uint32_t *)(0x40010400 + 0x00);//enable EXTI interrupt line (Enabling EXTI0)
	uint32_t *FTSR = (uint32_t *)(0x40010400 + 0x0C);//set falling edge trigger (button press pulls PA0 LOW)
	uint32_t *NVIC_ISER0 = (uint32_t *)0xE000E100;
	*APB2ENR |= (1<<4) | (1<<2) | (1<<0);
	//setting up the led blink
	*CRH &= ~(0xF<<20);
	*CRH |= (1<<20);
	//setting up the button input below
	*CRL &= ~(0xF<<0);
	*CRL |= (1<<2);
	//note: NEVER ASSUME THE STATE OF A REGISTER!! always clear it first then set
	*EXTICR1 &= ~(0xF<<0); //here as I am using PA0 so default case so making sure all bits are zeor
	*IMR &= ~(1<<0);
	*IMR |= (1<<0);
	*FTSR &= ~(1<<0);
	*FTSR |= (1<<0);
//no need for PR here because in PR, 0 bit means no interrupt pending and 1 bit means interrupt has fired and is waiting to be handled
	*NVIC_ISER0 |= (1<<6);
	while(1){
	}
}

void EXTI0_IRQHandler(void){
	*ODR ^= (1<<13);
	for(int i=0; i<1000; i++);
	//debounce: as one physical switch press might trigger multiple interrupts,delay PR clear so ODR toggles once per physical press
	*PR |= (1<<0);//basically the interrupt have been handled and now the flag is to be cleared.
}
