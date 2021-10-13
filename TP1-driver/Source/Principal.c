#include "stm32f10x.h"
#include "Driver_GPIO.h"

MyGPIO_Struct_TypeDef LED_Externe;	
MyGPIO_Struct_TypeDef Bouton_Externe;	


int main( void )
{
LED_Externe.GPIO = GPIOC;
LED_Externe.GPIO_Pin =10;
LED_Externe.GPIO_Conf = Out_OD;
	
Bouton_Externe.GPIO = GPIOC;
Bouton_Externe.GPIO_Pin =8;
Bouton_Externe.GPIO_Conf = In_PullUp;	
	
MyGPIO_Init(&LED_Externe);
MyGPIO_Init(&Bouton_Externe);
	
do
{
	/* Test allumé/éteint
	if((MyGPIO_Read(GPIOC,8)) == 0){
		MyGPIO_Set(GPIOC,10);
	}
	else{
		MyGPIO_Reset(GPIOC,10);
	}
	*/
	
	if((MyGPIO_Read(GPIOC,8)) == 0){ //test toggle
		MyGPIO_Toggle(GPIOC,10);
	}
	
	/*
	Bouton_Externe.GPIO_Conf = In_Floating;	
	MyGPIO_Init(&Bouton_Externe);
	Bouton_Externe.GPIO_Pin =0;
	Bouton_Externe.GPIO_Conf = In_PullDown;	
	MyGPIO_Init(&Bouton_Externe);
	Bouton_Externe.GPIO_Conf = In_Analog;	
	MyGPIO_Init(&Bouton_Externe);
	Bouton_Externe.GPIO_Conf = Out_Ppull;	
	MyGPIO_Init(&Bouton_Externe);
	Bouton_Externe.GPIO_Conf = AltOut_Ppull;	
	MyGPIO_Init(&Bouton_Externe);
	Bouton_Externe.GPIO_Conf = AltOut_OD;	
	MyGPIO_Init(&Bouton_Externe);
*/
	
}while (1) ;
};
