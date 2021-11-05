#include "bordage.h"
#include "MyTimer.h"
#include "Driver_GPIO.h"
#include <stdlib.h>

#define TIMservo TIM3
#define TIMservo_Channel 1
#define TIMcoder TIM2
#define GpioServo_out GPIOA
#define PinServo_out 6
#define GpioCoderIndex GPIOA
#define PinCoderIndex 2

static MyTimer_Struct_TypeDef MonTimer;
static MyTimer_Struct_TypeDef MonServo;
static MyGPIO_Struct_TypeDef Timer_Output;
static MyGPIO_Struct_TypeDef Coder_Index;

void IT_function (void){

}

void bordage_Init_Codeur(){
	MonTimer.Timer = TIMcoder;
	MonTimer.ARR = 360-1; 
	MonTimer.PSC = 2-1;
	MyTimer_Base_Init ( &MonTimer );
	MyTimer_Incremental_Coder_Mode(TIMcoder);
  MyTimer_Base_Start(TIMcoder);
	
	Coder_Index.GPIO = GpioCoderIndex;
	Coder_Index.GPIO_Pin = PinCoderIndex;
	Coder_Index.GPIO_Conf = In_PullDown;
	MyGPIO_Init (&Coder_Index);
	//PA2 connecté a EXTI2

	
//	MyTimer_ActiveIT(TIM2, 4, IT_function); // Interruption de débordement de CNT
}

int bordage_calcul_rapport_cyclique(int angle){
	int alpha = abs(angle - 180);
	return ((alpha)*500/135 + 6700/20);
}

void bordage_init_servo(){
		Timer_Output.GPIO = GpioServo_out;
		Timer_Output.GPIO_Conf =AltOut_Ppull;	
		Timer_Output.GPIO_Pin = PinServo_out;
//	TIM1->BDTR |= TIM_BDTR_MOE;
		MyGPIO_Init (&Timer_Output);
		MonServo.Timer = TIMservo;
		MonServo.ARR = 10000-1;
		MonServo.PSC = 144-1;
		MyTimer_Base_Init (&MonServo);
		MyTimer_PWM(MonServo.Timer , TIMservo_Channel);
		MyTimer_Base_Start(MonServo.Timer);
}

void bordage_Orienter_Servo(int duty_cycle){
		MyTimer_Set_DutyCycle(MonServo.Timer, TIMservo_Channel, duty_cycle); //duty cycle ab,cd% -> abcd
}

int bordage_get_angle(){
	return MyTimer_Read_CNT(TIMcoder);
}
