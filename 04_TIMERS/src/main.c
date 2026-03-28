/*
 * 04_TIMRES
 * Bare metal - zero HAL - direct register access
 * STM32F103C8T6
 */
#include <stdint.h>

uint32_t *SR = (uint32_t *)(0x40000000 + 0x10);
uint32_t *ODR = (uint32_t *)(0x40011000 + 0x0C);

int main(){
    uint32_t *APB2ENR = (uint32_t *)(0x40021000 + 0x18);
    uint32_t *CRH = (uint32_t *)(0x40011000 + 0x04);
    uint32_t *APB1ENR = (uint32_t *)(0x40021000 + 0x1C);
    uint32_t *CR1 = (uint32_t *)(0x40000000 + 0x00);
    uint32_t *PSC = (uint32_t *)(0x40000000 + 0x28);
    uint32_t *ARR = (uint32_t *)(0x40000000 + 0x2C);
    uint32_t *DIER = (uint32_t *)(0x40000000 + 0x0C);
    uint32_t *NVIC_ISER0 = (uint32_t *)0xE000E100;
    
    *ODR |= (1<<13);
    *APB2ENR |= (1<<4);
    *CRH &= ~(0xF<<20);
    *CRH |= (1<<20);

    *APB1ENR |= (1<<0);
    *PSC = 7999;
    *ARR = 999;
    *DIER |= (1<<0);
    *NVIC_ISER0 |= (1<<28);
    *CR1 |= (1<<0);
    while(1){
    }
}

void  TIM2_IRQHandler(void){
    *ODR ^= (1<<13);
    *SR &= ~(1<<0);
}
