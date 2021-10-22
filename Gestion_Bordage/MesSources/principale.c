#include "stm32f10x.h"
#include "MyTimer.h"
#include "Driver_GPIO.h"
#include "MyADC.h"

static MyTimer_Struct_TypeDef MonTimer;

static MyGPIO_Struct_TypeDef LED_Externe;	

static MyGPIO_Struct_TypeDef Timer_Output;


//void IT_function (void){

//MyGPIO_Toggle(LED_Externe.GPIO, LED_Externe.GPIO_Pin) ;
//}

int main(){
	LED_Externe.GPIO = GPIOC;
	LED_Externe.GPIO_Pin =10;
	LED_Externe.GPIO_Conf = Out_OD;
	MyGPIO_Init(&LED_Externe);
	MonTimer.Timer = TIM2;
	MonTimer.ARR = 100-1; //72MEG / (ARR+1*PSC+1)
	MonTimer.PSC = 1-1;
	MyTimer_Base_Init ( &MonTimer );
  MyTimer_Base_Start(TIM2);
// 	MyTimer_ActiveIT (TIM2, 4, IT_function);

//		MonTimer.Timer = TIM2;
//		MonTimer.ARR = 720-1; //72MEG / (ARR+1*PSC+1)
//		MonTimer.PSC = 1-1;
	
		Timer_Output.GPIO = GPIOA;
		Timer_Output.GPIO_Conf =AltOut_Ppull;	
		Timer_Output.GPIO_Pin = 3 + 7;
		TIM1->BDTR |= TIM_BDTR_MOE;
		MyGPIO_Init (&Timer_Output);

		MyTimer_Incremental_Coder_Mode(TIM2);
//		MyTimer_Base_Init (&MonTimer);
//		MyTimer_PWM(MonTimer.Timer , 3);
//		Set_DutyCycle(MonTimer.Timer, 3, 2000);
//		MyTimer_Base_Start(MonTimer.Timer);

//			Init_ADC_Single_Conv(ADC1,1);
//			ADC_Start(ADC1,4);
	while(1);
}

