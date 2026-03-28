/*
 * 05_UART
 * Bare metal - zero HAL - direct register access
 * STM32F103C8T6
 */

#include <stdint.h>
int main(void){
    char* str = "Hello World";
    uint32_t *USART1 = (uint32_t *)(0x40013800);
    uint32_t *APB2ENR = (uint32_t *)(0x40021000 + 0x18);
    uint32_t *CRH = (uint32_t *)(0x40010800 + 0x04); //PA9 and 10 pins so GPIOA
    uint32_t *SR = (uint32_t *)(0x40013800 + 0x00);
    uint32_t *DR = (uint32_t *)(0x40013800 + 0x04);
    uint32_t *BRR = (uint32_t *)(0x40013800 + 0x08);
    uint32_t *CR1 = (uint32_t *)(0x40013800 +0x0C);
    uint32_t *ODR = (uint32_t *)(0x40011000 + 0x0C);
    uint32_t *GPIOC_CRH = (uint32_t *)(0x40011000 + 0x04);
    //Enable Clock and GPIO pins
    *APB2ENR |= (1<<14) | (1<<2);
    *CRH &= ~(0xf<<4);
    *CRH |= (0x9<<4);
    *CRH &= ~(0xf<<8);
    *CRH |= (0x4<<8);
    //Setting up the baud rate
    *BRR = 833;
     //enable the USART n transmitter and reciever
    *CR1 |= (1<<13) | (1<<3);
    for(int i=0; str[i] != '\0'; i++){
        //Check TXE flag 
        while(!(*SR & (1<<7)));
        //Write DR 
        *DR = str[i];
    };
    //Check TC flag
    while(!(*SR & (1<<6)));
    while(1);
}
