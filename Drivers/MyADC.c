#include "MyADC.h"
#include "math.h"
float Init_ADC_Single_Conv(ADC_TypeDef * ADC, u16 Duree_Ech_us){
	int i;	 
	float SampleTimeSelection[8] = {0.0139*1.5,0.0139*7.5,0.0139*13.5,0.0139*28.5,0.0139*41.5,0.0139*55.5,0.0139*71.5,0.0139*239.5};
	float SampleTimeCalc[8] = {0.0139*1.5,0.0139*7.5,0.0139*13.5,0.0139*28.5,0.0139*41.5,0.0139*55.5,0.0139*71.5,0.0139*239.5};
	float CalcSampleTime = 10.0;
	char index_value;
	
	
	RCC->APB2ENR|=RCC_APB2ENR_ADC1EN;
	RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;
	ADC->CR2 |= ADC_CR2_ADON;
	ADC->CR2 &= ~ADC_CR2_CONT;
	ADC->CR2 |= ADC_CR2_EXTTRIG;  /// IL MANQUAIT CETTE LIGNE
	ADC->CR2 |= (ADC_CR2_EXTSEL_0 |ADC_CR2_EXTSEL_1 |ADC_CR2_EXTSEL_2);
			
			
			for (i = 0;i<8;i++){
				SampleTimeCalc[i] = fabs(SampleTimeCalc[i] - Duree_Ech_us);
			}

			for (i = 0;i<8;i++){
				if (SampleTimeCalc[i]<CalcSampleTime){
					index_value = i;
					CalcSampleTime = SampleTimeCalc[i];
				}
			}
			for (i = 0;i<10;i++){ 
			ADC->SMPR2 |= (index_value)<< 3*i;
			}
			for (i = 0;i<8;i++){ 
			ADC->SMPR1 |= (index_value)<< 3*i;
			}
			ADC->CR2 |= ADC_CR2_CAL;
			return SampleTimeSelection[index_value];
}


void ADC_Start(ADC_TypeDef * ADC, char Channel){
	ADC->SQR1 &= ~ADC_SQR1_L_0;
	ADC->SQR1 &= ~ADC_SQR1_L_1;
	ADC->SQR1 &= ~ADC_SQR1_L_2;
	if (Channel < 18 ){
		ADC->SQR3 |= Channel;
	}
	ADC->CR2 |=ADC_CR2_SWSTART;
}

