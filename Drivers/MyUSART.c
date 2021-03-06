#include "MyUSART.h"

static void (*HandlerUart1)(void);
static void (*HandlerUart2)(void);
static void (*HandlerUart3)(void);

void MyUSART_Init (MyUART_Struct_TypeDef * MyUart) {
	
	if (MyUart->Uart == USART1)
	{
		RCC -> APB2ENR |= RCC_APB2ENR_USART1EN;
		MyUart->Uart->BRR = 72000000/(MyUart->Debit);
	}
	if (MyUart->Uart == USART2)
	{
		RCC -> APB1ENR |= RCC_APB1ENR_USART2EN;
		MyUart->Uart->BRR = 36000000/(MyUart->Debit);
	}
	if (MyUart->Uart == USART3)
	{
		RCC -> APB1ENR |= RCC_APB1ENR_USART3EN;
		MyUart->Uart->BRR = 36000000/(MyUart->Debit);
	}
	
	MyUart->Uart ->CR1 |= USART_CR1_UE;
	MyUart->Uart->CR1 &= ~USART_CR1_M; //On aura 1 bit de Start, 8 bits de donn?es
	MyUart->Uart->CR2 &= ~USART_CR2_STOP; //!!!!!!!!On choisit de mettre STOP ? 00, pour un 1 bit de stop
	

	MyUart->Uart -> CR1 |= USART_CR1_RE ;
	MyUart->Uart -> CR1 |= USART_CR1_TE ;
}

void MyUSART_Active_IT (MyUART_Struct_TypeDef * MyUart, void(*IT_function) (void)) {
	MyUart->Uart->CR1 |= USART_CR1_RXNEIE;
	
	if (MyUart->Uart == USART1)
	{
		HandlerUart1 = IT_function;
		NVIC->IP[USART1_IRQn] = MyUart->Prio <<4;
		NVIC->ISER[1] |= NVIC_ISER_SETENA_5;
	}
	if (MyUart->Uart == USART2)
	{
		HandlerUart2 = IT_function;
		NVIC->IP[USART2_IRQn] = MyUart->Prio <<4;
		NVIC->ISER[1] |= NVIC_ISER_SETENA_6;
	}
	if (MyUart->Uart == USART3)
	{
		HandlerUart3 = IT_function;
		NVIC->IP[USART3_IRQn] = MyUart->Prio <<4;
		NVIC->ISER[1] |= NVIC_ISER_SETENA_7;
	}
	
}

char MyUSART_Get_Byte(USART_TypeDef * Uart)
{
	return Uart->DR;
}

void USART1_IRQHandler(void){
	USART1->SR &= ~USART_SR_RXNE; // On remet le flag ? 0
	//Message = USART1->DR;
	if (HandlerUart1 !=0){
	(*HandlerUart1) ();
	}
	//PWM
	}

void USART2_IRQHandler(void){
	USART2->SR &= ~USART_SR_RXNE; // On remet le flag ? 0
	//Message = USART2->DR;
	if (HandlerUart2 !=0){
	(*HandlerUart2) ();
	}
	}

void USART3_IRQHandler(void){
	USART3->SR &= ~USART_SR_RXNE; // On remet le flag ? 0
	//Message = USART3->DR;
	if (HandlerUart3 !=0){
	(*HandlerUart3) ();
	}
	}

	void MyUSART_Send_Byte(USART_TypeDef * Uart, char Byte){
		Uart->DR =  Byte;
	}
