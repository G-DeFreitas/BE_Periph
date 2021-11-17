#include "MyTransmission.h"
#include "MyADC.h"
#include "Driver_GPIO.h"
#include "MyUSART.h"
#include <stdlib.h>

#define ADC ADC1
#define ADCchan 10

#define Duree_Ech 10000

#define ref 20

static MyUART_Struct_TypeDef muart;
static MyGPIO_Struct_TypeDef servo;
static MyGPIO_Struct_TypeDef bitsens;
static MyGPIO_Struct_TypeDef uartTx;
static MyGPIO_Struct_TypeDef uartRx;
static MyTimer_Struct_TypeDef timServo;

static const char bat_faible[15] = "Batterie faible";
static const char msg_angle[7] = "angle :";

char * toArray(int number) //renvoie un tableau des 3 premiers chiffres de largument en char
{
    int n = 3;
    int i;
    char *numberArray = calloc(n, sizeof(char));
    for (i = n-1; i >= 0; --i, number /= 10)
    {
        numberArray[i] = (number % 10) + '0';
    }
    return numberArray;
}



void MyTransmission_InitADCbat(void){
	Init_ADC_Single_Conv(ADC, Duree_Ech);
};


//Renvoie le niveau de la batterie
int MyTransmission_NiveauBat(void){
	ADC_Start(ADC, ADCchan);
	return ADC->DR;
};

//PE en decimal c'est 1145 
int MyTransmission_BatterieFaible(char RefBatFaible){
	if ( MyTransmission_NiveauBat()*100 <= RefBatFaible*1145){
		return 1;
	}
	else
	{
		return 0;
	}
	
}

void MyTransmission_InitUart (){
		// Config USART
  muart.Debit=9600;
	muart.Prio = 4;
	muart.Uart=USART1;
	
//Config Bit de Sens
	bitsens.GPIO = GPIOA;
	bitsens.GPIO_Conf = Out_Ppull;
	bitsens.GPIO_Pin = 8;
	MyGPIO_Init ( &bitsens );
	
//Config Servo
	servo.GPIO = GPIOB;
	servo.GPIO_Conf = AltOut_Ppull;
	servo.GPIO_Pin = 6;
	MyGPIO_Init ( &servo );
	
//Config Tim
	timServo.Timer = TIM4;
	timServo.ARR = 720-1;
	timServo.PSC = 1-1;
	MyTimer_Base_Init (&timServo);
	
//Config Uart Tx
	uartTx.GPIO = GPIO_UART1;
	uartTx.GPIO_Conf = AltOut_Ppull;
	uartTx.GPIO_Pin = TxPin_UART1;
	MyGPIO_Init ( &uartTx );

//Config Uart Rx
	uartRx.GPIO = GPIO_UART1;
	uartRx.GPIO_Conf = In_PullUp;
	uartRx.GPIO_Pin = RxPin_UART1;
	MyGPIO_Init ( &uartRx );
	
	MyUSART_Init (&muart);
	}

void MyTransmission_Send(int angle){
	

	//On suppose l'uart dejà initialisé
	if (MyTransmission_BatterieFaible(ref) == 1){
		int i;
		for (i=0; i<15;i++){
			MyUSART_Send_Byte(muart.Uart, bat_faible[i]);
			while((muart.Uart->SR & USART_SR_TXE) ==0);
			}
		MyUSART_Send_Byte(muart.Uart, '\n');
		while((muart.Uart->SR & USART_SR_TXE) ==0);
	}
	else
	{
		int i;
		for (i=0; i<7;i++){
			MyUSART_Send_Byte(muart.Uart, msg_angle[i]);
			while((muart.Uart->SR & USART_SR_TXE) == 0);
		}
		for (i=0; i<3;i++){
			MyUSART_Send_Byte(muart.Uart, toArray(angle)[i]);
			while((muart.Uart->SR & USART_SR_TXE) == 0);
		}
		MyUSART_Send_Byte(muart.Uart, '\n');
		while((muart.Uart->SR & USART_SR_TXE) ==0);
	}
}
