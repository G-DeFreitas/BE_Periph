#include "MyTransmission.h"
#include "MyADC.h"
#include "Driver_GPIO.h"
#include "MyUSART.h"

#define ADC ADC1
#define ADCchan 10

#define Duree_Ech 10000

#define ref 20
static const char bat_faible[15] = "Batterie faible";
static const char msg_angle[7] = "angle :";
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

void MyTransmission_Send(MyUART_Struct_TypeDef MyUart){
	

	//On suppose l'uart dejà initialisé
	if (MyTransmission_BatterieFaible(ref)){
		int i;
		for (i=0; i<15;i++){
			MyUSART_Send_Byte(MyUart.Uart, bat_faible[i]);
			while((MyUart.Uart->SR & USART_SR_TXE) ==0);
			}
	}
	else
	{
		int i;
		for (i=0; i<7;i++){
			MyUSART_Send_Byte(MyUart.Uart, msg_angle[i]);
			while((MyUart.Uart->SR & USART_SR_TXE) == 0);
		}
	}
}
