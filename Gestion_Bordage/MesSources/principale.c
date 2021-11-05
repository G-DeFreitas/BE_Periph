#include "bordage.h"

//// TEST DE LA COMMANDE DU SERVO
#include "MyTimer.h"
static MyTimer_Struct_TypeDef MonTimer;
void Interruption (void) {
	bordage_Orienter_Servo(bordage_calcul_rapport_cyclique(bordage_get_angle()));
}


//static MyGPIO_Struct_TypeDef LED_Externe;	

//static MyGPIO_Struct_TypeDef Timer_Output;


//void IT_function (void){

//MyGPIO_Toggle(LED_Externe.GPIO, LED_Externe.GPIO_Pin) ;
//}



int main(){
	bordage_Init_Codeur();
	bordage_init_servo();
	bordage_Orienter_Servo(bordage_calcul_rapport_cyclique(bordage_get_angle()));	
	
	//// TEST DE LA COMMANDE DU SERVO
	MonTimer.ARR = 10000-1;
	MonTimer.PSC = 72-1;
	MonTimer.Timer = TIM4;
	MyTimer_Base_Init(&MonTimer);
	MyTimer_ActiveIT(TIM4,3,Interruption);
	MyTimer_Base_Start (TIM4);


	while(1);
}

