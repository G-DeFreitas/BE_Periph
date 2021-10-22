#include "bordage.h"

//static MyTimer_Struct_TypeDef MonTimer;

//static MyGPIO_Struct_TypeDef LED_Externe;	

//static MyGPIO_Struct_TypeDef Timer_Output;


//void IT_function (void){

//MyGPIO_Toggle(LED_Externe.GPIO, LED_Externe.GPIO_Pin) ;
//}

int main(){
	bordage_Init_Codeur();
	bordage_init_servo();
	bordage_Orienter_Servo(bordage_calcul_rapport_cyclique(bordage_get_angle()));
	//bordage_Orienter_Servo(1201);

	while(1)
	{	bordage_Orienter_Servo(bordage_calcul_rapport_cyclique(bordage_get_angle()));}	
	;
}

