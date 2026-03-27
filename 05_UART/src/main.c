/*
 * 05_UART: Button on PA0 toggles LED on PC13
 * Bare metal - zero HAL - direct register access
 * STM32F103C8T6
 */

#include <stdint.h>
int main(void){
    uint32_t *USART1 = (uint32_t *)(0x40013800);
    uint32_t *APB2ENR = (uint32_t *)(0x40021000 + 0x18);
    uint32_t *CRH = (uint32_t *)(0x40010800 + 0x04); //PA9 and 10 pins so GPIOA
    uint32_t *SR = (uint32_t *)(0x40013800 + 0x00);
    uint32_t *DR = (uint32_t *)(0x40013800 + 0x04);
    uint32_t *BRR = (uint32_t *)(0x40013800 + 0x08);
    uint32_t *CR1 = (uint32_t *)(0x40013800 +0x0C);
    //Enable Clock and GPIO pins
    *APB2ENR |= (1<<14) | (1<<2);
    *CRH &= ~(0xf<<4);
    *CRH |= (0x9<<4);
    *CRH &= ~(0xf<<8);
    *CRH |= (0x4<<8);
     //enable the USART n transmitter and reciever
    *CR1 |= (1<<13) | (1<<3);
    //Setting up the baud rate
    *BRR = 833;
    //Check TXE flag 
    while(!(*SR & (1<<7)));
    //Write DR 
    *DR = 'H';
    //Check TC flag
    while(!(*SR & (1<<6)));
    while(1);
}