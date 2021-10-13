#include "stm32f10x.h"
#include "Driver_GPIO.h"

void MyGPIO_Init ( MyGPIO_Struct_TypeDef * GPIOStructPtr ) {
	if (GPIOStructPtr->GPIO == GPIOA){
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	}
	else	if (GPIOStructPtr->GPIO == GPIOB){
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	}
	else	if (GPIOStructPtr->GPIO == GPIOC){
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	}
	else	if (GPIOStructPtr->GPIO == GPIOD){
	RCC->APB2ENR |= RCC_APB2ENR_IOPDEN;
	}
	
	if (GPIOStructPtr->GPIO_Conf != 0x9){
		if (GPIOStructPtr->GPIO_Pin <= 7) {
		GPIOStructPtr->GPIO->CRL &= ~(0xF << GPIOStructPtr->GPIO_Pin*4);
		GPIOStructPtr->GPIO->CRL |= (GPIOStructPtr->GPIO_Conf << GPIOStructPtr->GPIO_Pin*4);
		}
		else
		{
		GPIOStructPtr->GPIO->CRH &= ~(0xF << (GPIOStructPtr->GPIO_Pin-8)*4);
		GPIOStructPtr->GPIO->CRH |= (GPIOStructPtr->GPIO_Conf << (GPIOStructPtr->GPIO_Pin-8)*4);
		}
		GPIOStructPtr->GPIO->ODR &= ~(0x1 << GPIOStructPtr->GPIO_Pin);
	}
	else{
				if (GPIOStructPtr->GPIO_Pin <= 7) {
		GPIOStructPtr->GPIO->CRL &= ~(0xF << GPIOStructPtr->GPIO_Pin*4);
		GPIOStructPtr->GPIO->CRL |= (GPIOStructPtr->GPIO_Conf << GPIOStructPtr->GPIO_Pin*4);
		}
		else
		{
		GPIOStructPtr->GPIO->CRH &= ~(0xF << (GPIOStructPtr->GPIO_Pin-8)*4);
		GPIOStructPtr->GPIO->CRH |= (0x8 << (GPIOStructPtr->GPIO_Pin-8)*4);
		}
		GPIOStructPtr->GPIO->ODR |= (0x1 << GPIOStructPtr->GPIO_Pin);
	}
}

int MyGPIO_Read(GPIO_TypeDef * GPIO , char GPIO_Pin ) { // renvoie 0 ou autre chose d i f f e r e n t de 0
return GPIO->IDR & (0x1 << GPIO_Pin);
}
	void MyGPIO_Set(GPIO_TypeDef * GPIO , char GPIO_Pin ) {
		GPIO->BSRR = 0x01<<GPIO_Pin;
	}
void MyGPIO_Reset(GPIO_TypeDef * GPIO , char GPIO_Pin ) {
		GPIO->BRR = 0x01<<GPIO_Pin;
}

void MyGPIO_Toggle(GPIO_TypeDef * GPIO , char GPIO_Pin ) {
		GPIO->ODR ^= (0x1 << GPIO_Pin);
}