/**
 ******************************************************************************
 * 03_I2C
 * Bare metal - zero HAL - direct register access
 * STM32F103C8T6
 ******************************************************************************
 */

#include <stdint.h>
int main(void)
{
	uint32_t *APB2ENR = (uint32_t *)(0x40021000 + 0x18);//GPIOB is here
	uint32_t *APB1ENR = (uint32_t *)(0x40021000 + 0x1C);//I2C1 is here
	uint32_t *CRL = (uint32_t *)(0x40010C00 + 0x00);//PB7 and PB6
	uint32_t *CR1 = (uint32_t *)(0x40005000 + 0x00);//Enable i2C peripheral
	uint32_t *CR2 = (uint32_t *)(0x40005000 + 0x04);//Enable peripheral clock frequency
	uint32_t *CCR = (uint32_t *)(0x40005000 + 0x1C);//Enables I2C bus frequency
	uint32_t *DR = (uint32_t *)(0x40005000 + 0x10);//Enables data register
	uint32_t *SR1 = (uint32_t *)(0x40005000 + 0x14);//To check ACK
	uint32_t *SR2 = (uint32_t *)(0x40005000 + 0x18);//To read and clear ACK
	uint32_t *Trise = (uint32_t *)(0x40005000 + 0x20);//To configure max rise time
	
	uint32_t *CRH = (uint32_t *)(0x40011000 + 0x04);
	uint32_t *ODR = (uint32_t *)(0x40011000 + 0x0C);
	
	*APB2ENR |= (1<<3) | (1<<4) | (1<<0);
	*APB1ENR |= (1<<21);
	//led setup
	*CRH &= ~(0xF << 20);
	*CRH |= (1<<20); 
	//i2c setup
	*CRL &= ~((0xf<<24)|(0xf<<28));
	*CRL |= (0xd<<24)|(0xd<<28);
	*CR2 &= ~(0x3f<<0);
	*CR2 |= (1<<3);
	*CCR &= ~(0xfff << 0);
	*CCR |= (40 << 0);// 100kHz I2C speed with 8MHz APB1 clock required
	*Trise &= ~(0x3f << 0 );
	*Trise |=(0x9<<0);//For standard mode 100kHz with 8Mhz
	*CR1 |=(1<<0);//Enable the peripheral bit (PE)
	__asm("nop");
	*CR1 |= (1<<8);//generates START condition
	*ODR |= (1<<13); //check if code reached
	while(!(*SR1 & (1<<0)));//Until START condition is sent SR1's 0bit will stay zero and loop will keep running
	*DR = 0x78;//Address for the oled display is 0x3c and R/W needs 0(for writing) so 0x3c<<1 hence R/W at bit 0 is 0
	while(!(*SR1 & (1<<1)));//Until it is confirmed that address is acknowledged loop will run
	(void)(*SR2);//Read SR2 to clear ADDR flag
	*DR = 0x00;//Dummy byte to prove that I2C is working
	while(!(*SR1 & (1<<7)));//Confirms Data register is empty now
	*CR1 |=(1<<9);//Generate STOPs. STOPs the whole peripheral
}
