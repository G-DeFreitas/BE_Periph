#include "stm32f10x.h"
#include "Driver_GPIO.h"

static void (*HandlerContent0)(void);
static void (*HandlerContent1)(void);
static void (*HandlerContent2)(void);
static void (*HandlerContent3)(void);

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

void MyGPIO_Interrupt(GPIO_TypeDef * GPIO , void(*IT_function) (void) , char GPIO_Pin, char Prio){
	int mask;
	if (GPIO == GPIOA) {
		mask = AFIO_EXTICR1_EXTI0_PA;
	}
	else if (GPIO == GPIOB) {
		mask = AFIO_EXTICR1_EXTI0_PB;
	}
	else if (GPIO == GPIOC) {
		mask = AFIO_EXTICR1_EXTI0_PC;
	}
	else if (GPIO == GPIOD) {
		mask = AFIO_EXTICR1_EXTI0_PD;
	}
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	AFIO->EXTICR[0] |= mask << 4*GPIO_Pin;
	EXTI->RTSR |= EXTI_RTSR_TR0 << GPIO_Pin ;
	EXTI->FTSR &= ~(EXTI_RTSR_TR0) << GPIO_Pin;
	EXTI->IMR |= EXTI_IMR_MR0 << GPIO_Pin;
	EXTI->PR |= EXTI_PR_PR0 << GPIO_Pin;
	switch (GPIO_Pin) {
	case 0 :
 	HandlerContent0 = IT_function;
	break;
	case 1 :
 HandlerContent1 = IT_function;
	break;
	case 2 :
  HandlerContent2 = IT_function;
	break;
	case 3 :
  HandlerContent3 = IT_function;
	break;
	} 
	NVIC->IP[EXTI0_IRQn + GPIO_Pin] = Prio <<4;
	NVIC->ISER[0] |= NVIC_ISER_SETENA_6 << GPIO_Pin;
}




	void EXTI0_IRQHandler(void){
		EXTI->PR |= EXTI_PR_PR0;
		if (HandlerContent0 !=0){(*HandlerContent0) ();}
	}

		void EXTI1_IRQHandler(void){
		EXTI->PR |= EXTI_PR_PR1;
		if (HandlerContent1 !=0){(*HandlerContent1) ();}
	}
			void EXTI2_IRQHandler(void){
		EXTI->PR |= EXTI_PR_PR2;
		if (HandlerContent2 !=0){(*HandlerContent2) ();}
	}
				void EXTI3_IRQHandler(void){
		EXTI->PR |= EXTI_PR_PR3;
		if (HandlerContent3 !=0){(*HandlerContent3) ();}
	}
				