#include "stm32f10x.h"
int main( void )
{
RCC->APB2ENR |= (0x01 << 2) | (0x01 << 3) | (0x01 << 4) ; 
GPIOC->CRH &= ~(0xF <<8); // GPIOC 10 en sortie open drain
GPIOC->CRH |= 0x5 <<8;
	
GPIOC->CRH &= ~(0xF); // GPIOC 8 en Input pullup
GPIOC->CRH |= 0x8;
GPIOC->ODR |= GPIO_ODR_ODR8;
	
do
{
	if((GPIOC->IDR & 0x01<<8) == 0){
		GPIOC->BRR = 0x01<<10;
	}
	else{
			GPIOC->BSRR = 0x01<<10;
	}
}while (1) ;
};