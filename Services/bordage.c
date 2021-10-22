#include "bordage.h"
#include "MyTimer.h"
#include "Driver_GPIO.h"
#include <stdlib.h>

static MyTimer_Struct_TypeDef MonTimer;
static MyTimer_Struct_TypeDef MonServo;
static MyGPIO_Struct_TypeDef Timer_Output;


void IT_function (void){

}

void bordage_Init_Codeur(){
	MonTimer.Timer = TIM2;
	MonTimer.ARR = 360-1; 
	MonTimer.PSC = 2-1;
	MyTimer_Base_Init ( &MonTimer );
	MyTimer_Incremental_Coder_Mode(TIM2);
  MyTimer_Base_Start(TIM2);
//	MyTimer_ActiveIT(TIM2, 4, IT_function); // Interruption de débordement de CNT
}

int bordage_calcul_rapport_cyclique(int angle){
	int alpha = abs(angle - 180);
	return ((alpha)*500/135 + 6700/20);
}

void bordage_init_servo(){
		Timer_Output.GPIO = GPIOA;
		Timer_Output.GPIO_Conf =AltOut_Ppull;	
		Timer_Output.GPIO_Pin = 6 + 7;
//	TIM1->BDTR |= TIM_BDTR_MOE;
		MyGPIO_Init (&Timer_Output);
		MonServo.Timer = TIM3;
		MonServo.ARR = 1-1;
		MonServo.PSC = 1-1;
		MyTimer_Base_Init (&MonServo);
		MyTimer_PWM(MonServo.Timer , 1);
}
