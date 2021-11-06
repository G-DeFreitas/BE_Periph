#include "stm32f10x.h"
#include "MyTimer.h"
static void (*HandlerContent1)(void);
static void (*HandlerContent2)(void);
static void (*HandlerContent3)(void);
static void (*HandlerContent4)(void);


void MyTimer_Base_Init ( MyTimer_Struct_TypeDef * Timer ){
	if (Timer->Timer == TIM1) {
			RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
			TIM1->ARR = Timer->ARR;
			TIM1->PSC = Timer->PSC;

	}
	else if (Timer->Timer == TIM2) {
			RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
			TIM2->ARR = Timer->ARR;
			TIM2->PSC = Timer->PSC;
	}
	else if (Timer->Timer == TIM3) {
			RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
			TIM3->ARR = Timer->ARR;
			TIM3->PSC = Timer->PSC;
	}
	else if (Timer->Timer == TIM4) {
			RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
			TIM4->ARR = Timer->ARR;
			TIM4->PSC = Timer->PSC;
	}
}

void MyTimer_Incremental_Coder_Mode ( TIM_TypeDef * Timer ){
	Timer->CCMR1 |= TIM_CCMR1_CC1S_0;
	Timer->CCMR1 &= ~TIM_CCMR1_CC1S_1;
	Timer->CCMR1 |= TIM_CCMR1_CC2S_0;
	Timer->CCMR1 &= ~TIM_CCMR1_CC2S_1;
	Timer->CCER &= ~TIM_CCER_CC2P;
	Timer->CCER &= ~TIM_CCER_CC2NP;
	Timer->CCMR1 &= ~(TIM_CCMR1_IC2F_0 |TIM_CCMR1_IC2F_1 | TIM_CCMR1_IC2F_2 | TIM_CCMR1_IC2F_3 );
	Timer->CCER &= ~TIM_CCER_CC1P;
	Timer->CCER &= ~TIM_CCER_CC1NP;
	Timer->CCMR1 &= ~(TIM_CCMR1_IC1F_0 |TIM_CCMR1_IC1F_1 | TIM_CCMR1_IC1F_2 | TIM_CCMR1_IC1F_3 );
	Timer->SMCR &= ~TIM_SMCR_SMS_2;
	Timer->SMCR |= (TIM_SMCR_SMS_0 |TIM_SMCR_SMS_1);
	Timer->CR1 |= TIM_CR1_CEN;
}


void MyTimer_ActiveIT (TIM_TypeDef * Timer, char Prio, void(*IT_function) (void)){

	
	if (Timer == TIM1) {
	HandlerContent1 = IT_function;
	TIM1->DIER |= TIM_DIER_UIE;
	NVIC->IP[TIM1_UP_IRQn] = Prio <<4;
	NVIC->ISER[0] |= NVIC_ISER_SETENA_25;
	}
	else if (Timer == TIM2) {
	HandlerContent2 = IT_function;
	TIM2->DIER |= TIM_DIER_UIE;
	NVIC->IP[TIM2_IRQn] = Prio <<4;
	NVIC->ISER[0] |= NVIC_ISER_SETENA_28;
	}
	else if (Timer == TIM3) {
	HandlerContent3 = IT_function;
	TIM3->DIER |= TIM_DIER_UIE;
	NVIC->IP[TIM3_IRQn] = Prio <<4;
	NVIC->ISER[0] |= NVIC_ISER_SETENA_29;
	}
	else if (Timer == TIM4) {
	HandlerContent4 = IT_function;
	TIM4->DIER |= TIM_DIER_UIE;
	NVIC->IP[TIM4_IRQn] = Prio <<4;
	NVIC->ISER[0] |= NVIC_ISER_SETENA_30;	
	}

}

	void TIM1_UP_IRQHandler(void){
	TIM1->SR &= ~TIM_SR_UIF;
	if (HandlerContent1 !=0){
	(*HandlerContent1) ();
	}
}
	
		void TIM2_IRQHandler(void){
	TIM2->SR &= ~TIM_SR_UIF;
	if (HandlerContent2 !=0){
	(*HandlerContent2) ();
	}
}
			void TIM3_IRQHandler(void){
	TIM3->SR &= ~TIM_SR_UIF;
	if (HandlerContent3 !=0){
	(*HandlerContent3) ();
	}
}
		void TIM4_IRQHandler(void){
	TIM4->SR &= ~TIM_SR_UIF;
	if (HandlerContent4 !=0){
	(*HandlerContent4) ();
	}
}

void MyTimer_PWM(TIM_TypeDef * Timer , char Channel ) {
if (Timer == TIM1) {
TIM1->BDTR |= TIM_BDTR_MOE;
}
Timer->DIER |= TIM_DIER_CC1IE << (Channel-1);
Timer->CCER |= TIM_CCER_CC1E << 4 * (Channel-1); // CCxE mis à 1, x au Channel correspondant
	switch (Channel){
		case 1 :	
			Timer->CCMR1 |= (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1); 
			Timer->CCMR1 &= ~(TIM_CCMR1_OC1M_0); 
			break;
		case 2:
			Timer->CCMR1 |= (TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1); 
			Timer->CCMR1 &= ~(TIM_CCMR1_OC2M_0); 
			break;
		case 3:
			Timer->CCMR2 |= (TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1); 
			Timer->CCMR2 &= ~(TIM_CCMR2_OC3M_0); 
			break;
		case 4:
			Timer->CCMR2 |= (TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1); 
			Timer->CCMR2 &= ~(TIM_CCMR2_OC4M_0); 
	}
	//	MyGPIO_Struct_TypeDef Timer_Output;
//	if (Timer == TIM1){
//	Timer_Output.GPIO = GPIOA;
//	Timer_Output.GPIO_Conf =AltOut_Ppull;	
//	Timer_Output.GPIO_Pin = Channel + 7;
//	TIM1->BDTR |= TIM_BDTR_MOE;
//	}
//	else if (Timer == TIM2){
//	Timer_Output.GPIO = GPIOA;
//	Timer_Output.GPIO_Conf =AltOut_Ppull;	
//	Timer_Output.GPIO_Pin = Channel-1;
//	}
//	else if (Timer == TIM3){
//		if (Channel <= 2){
//			Timer_Output.GPIO = GPIOA;
//			Timer_Output.GPIO_Conf =AltOut_Ppull;	
//			Timer_Output.GPIO_Pin = Channel + 5;
//		}
//		else{
//			Timer_Output.GPIO = GPIOB;
//			Timer_Output.GPIO_Conf =AltOut_Ppull;	
//			Timer_Output.GPIO_Pin = Channel -3;
//		}
//	}
//	else if (Timer == TIM4){
//	Timer_Output.GPIO = GPIOB;
//	Timer_Output.GPIO_Conf =AltOut_Ppull;	
//	Timer_Output.GPIO_Pin = Channel + 5;
//	}
//	MyGPIO_Init (&Timer_Output);
}

void MyTimer_Set_DutyCycle(TIM_TypeDef * Timer, char Channel, int Duty_Cycle){ //duty cycle ab,cd% -> abcd
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

int MyTimer_Read_CNT(TIM_TypeDef * Timer){
	return Timer->CNT;
}
void MyTimer_Write_CNT(TIM_TypeDef * Timer, int Value){
	 Timer->CNT = Value;
}

