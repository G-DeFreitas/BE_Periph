#include "Timing.h"
#include "MyTimer.h"
static MyTimer_Struct_TypeDef MonTimer;


void Timing_Ordre(void (*Interruption)(void)){
	MonTimer.ARR = 10000-1;
	MonTimer.PSC = 72-1;
	MonTimer.Timer = TIM3;
	MyTimer_Base_Init(&MonTimer);
	MyTimer_ActiveIT(TIM3,3,Interruption);
	MyTimer_Base_Start (TIM3);
}
