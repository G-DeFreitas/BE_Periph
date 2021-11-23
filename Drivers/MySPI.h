#ifndef MYSPI_H
#define MYSPI_H
#include "stm32f10x.h"
#include "MyTimer.h"
#include "Driver_GPIO.h"


typedef struct
{
	signed int X;
	signed int Y;
	signed int Z;
} Axes_Struct_TypeDef ;

#define SPI SPI1
#define GPIO_SPI1 GPIOA
#define MISOPin_SPI1 6
#define MOSIPin_SPI1 7
#define nssPin_SPI1 4
#define sckPin_SPI1 5
#define chipselPin_SPI1 12

#define concat(first, second) first second
//Initialisation de l'USART
void MySPI_Init(void);
void SPI_Enable (void);
void SPI_Disable (void);
void CS_Set (void);
void CS_Reset (void);
void MySPI_Transmit (int toSend);
char MySPI_Receive(int data);
#endif
