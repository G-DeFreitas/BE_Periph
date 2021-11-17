#include "MyTransmission.h"
#include "MyADC.h"
#include "Driver_GPIO.h"

#define ADC ADC1

#define Duree_Ech 1000000

static MyGPIO_Struct_TypeDef BatGPIO;

void MyTransmission_InitADCbat(){
	Init_ADC_Single_Conv(ADC, 10000);
};

