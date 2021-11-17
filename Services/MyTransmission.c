#include "MyTransmission.h"
#include "MyADC.h"
#include "Driver_GPIO.h"

#define ADC ADC1
#define ADCchan 10

#define Duree_Ech 10000

void MyTransmission_InitADCbat(void){
	Init_ADC_Single_Conv(ADC, Duree_Ech);
};


//Renvoie le niveau de la batterie
int MyTransmission_NiveauBat(void){
	ADC_Start(ADC, ADCchan);
	return ADC->DR;
};

//PE en decimal c'est 1145 
int BatterieFaible(char RefBatFaible){
	if ( MyTransmission_NiveauBat()*100 < RefBatFaible*1145){
		return 1;
	}
	else
	{
		return 0;
	}
	
}
