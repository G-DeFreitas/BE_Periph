#include "stm32f10x.h"
#include "MyTimer.h"
#include "Driver_GPIO.h"
#include "MyADC.h"

//static MyTimer_Struct_TypeDef MonTimer;

static MyGPIO_Struct_TypeDef LED_Externe;	

//static MyGPIO_Struct_TypeDef Timer_Output;


void IT_function (void){

MyGPIO_Toggle(LED_Externe.GPIO, LED_Externe.GPIO_Pin) ;
}

void Set_DutyCycle(TIM_TypeDef * Timer, char Channel, int Duty_Cycle){ //duty cycle ab,cd% -> abcd
	int CCRx = ((Timer->ARR +1) * Duty_Cycle)/10000;
	switch (Channel){
		case 1:
		Timer->CCR1 =CCRx;
		break;
		case 2:
		Timer->CCR2 =CCRx;
		break;
		case 3:
		Timer->CCR3 =CCRx;
		break;
		case 4:
		Timer->CCR4 =CCRx;
		break;
	}
}

int main(){
//	LED_Externe.GPIO = GPIOC;
//	LED_Externe.GPIO_Pin =10;
//	LED_Externe.GPIO_Conf = Out_OD;
//	MyGPIO_Init(&LED_Externe);
//	MonTimer.Timer = TIM1;
//	MonTimer.ARR = 18000-1; //72MEG / (ARR+1*PSC+1)
//	MonTimer.PSC = 2000-1;
//	MyTimer_Base_Init ( &MonTimer );
//  MyTimer_Base_Start(TIM1);
//	MyTimer_ActiveIT (TIM1, 4, IT_function);

//		MonTimer.Timer = TIM1;
//		MonTimer.ARR = 720-1; //72MEG / (ARR+1*PSC+1)
//		MonTimer.PSC = 1-1;
//	
//		Timer_Output.GPIO = GPIOA;
//		Timer_Output.GPIO_Conf =AltOut_Ppull;	
//		Timer_Output.GPIO_Pin = 3 + 7;
//		TIM1->BDTR |= TIM_BDTR_MOE;
//		MyGPIO_Init (&Timer_Output);

//		MyTimer_Base_Init (&MonTimer);
//		MyTimer_PWM(MonTimer.Timer , 3);
//		Set_DutyCycle(MonTimer.Timer, 3, 2000);
//		MyTimer_Base_Start(MonTimer.Timer);

			Init_ADC_Single_Conv(ADC1,1);
			ADC_Start(ADC1,4);
	while(1);
}

