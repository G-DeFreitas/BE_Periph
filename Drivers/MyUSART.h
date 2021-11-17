#ifndef MYUSART_H
#define MYUSART_H
#include "stm32f10x.h"
#include "MyTimer.h"
#include "Driver_GPIO.h"

typedef struct
{
	USART_TypeDef * Uart ; // TIM1 à TIM4
	int Debit;
	int Prio;
} MyUART_Struct_TypeDef ;

//Valeurs des Pins et GPIO dans la datasheet page 30
#define TxPin_UART1 9
#define RxPin_UART1 10
#define GPIO_UART1 GPIOA

#define TxPin_UART2 2
#define RxPin_UART2 3
#define GPIO_UART2 GPIOA

#define TxPin_UART3 10
#define RxPin_UART3 11
#define GPIO_UART3 GPIOB

//Initialisation de l'USART
void MyUSART_Init( MyUART_Struct_TypeDef * MyUart);

//Réception
#define MyUSART_Reception() ( USART1 -> CR1 |= USART_CR1_RE )

//Envoi
#define MyUSART_Transmission() ( USART1 -> CR1 |= USART_CR1_TE )

char MyUSART_Get_Byte(USART_TypeDef * Uart);

//
void MyUSART_Send_Byte(USART_TypeDef * Uart, char Byte);
//Activer Interruption
void MyUSART_Active_IT (MyUART_Struct_TypeDef * MyUart, void(*IT_function) (void));



#endif
