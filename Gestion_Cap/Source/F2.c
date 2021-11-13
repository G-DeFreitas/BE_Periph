#include "MyUSART.h"

MyUART_Struct_TypeDef muart;
MyGPIO_Struct_TypeDef servo;
MyGPIO_Struct_TypeDef bitsens;
MyGPIO_Struct_TypeDef uartTx;
MyGPIO_Struct_TypeDef uartRx;
MyTimer_Struct_TypeDef timServo;

signed char monMess;

void USART_CallBack (void) {
		monMess = MyUSART_Get_Byte(muart.Uart);
	
		//Passer PA2 en Output
	
		//PA6 en PWM
		
		if (monMess >= 0) {
			//Change valeur PA8 en fonction du bit de sens = 0 (reset pa2)
			MyGPIO_Reset(bitsens.GPIO, bitsens.GPIO_Pin) ;
		}
		else {
			//Change valeur PA8 en fonction du bit de sens = 1 (set pa2)
			MyGPIO_Set(bitsens.GPIO, bitsens.GPIO_Pin) ;
			// inverser message
			monMess = - monMess;
		}
		
		//Règle PWM sur PA6 en fontion de la valeur message*/
		
		MyTimer_PWM(timServo.Timer, 1 );
		Set_DutyCycle(timServo.Timer, 1, monMess*100);
		MyTimer_Base_Start(timServo.Timer);
	}

void f2 () {
	// Config USART
  muart.Debit=9600;
	muart.Prio = 4;
	muart.Uart=USART1;
	
//Config Bit de Sens
	bitsens.GPIO = GPIOA;
	bitsens.GPIO_Conf = Out_Ppull;
	bitsens.GPIO_Pin = 8;
	MyGPIO_Init ( &bitsens );
	
//Config Servo
	servo.GPIO = GPIOB;
	servo.GPIO_Conf = AltOut_Ppull;
	servo.GPIO_Pin = 6;
	MyGPIO_Init ( &servo );
	
//Config Tim
	timServo.Timer = TIM4;
	timServo.ARR = 720-1;
	timServo.PSC = 1-1;
	MyTimer_Base_Init (&timServo);
	
//Config Uart Tx
	uartTx.GPIO = GPIO_UART1;
	uartTx.GPIO_Conf = AltOut_Ppull;
	uartTx.GPIO_Pin = TxPin_UART1;
	MyGPIO_Init ( &uartTx );

//Config Uart Rx
	uartRx.GPIO = GPIO_UART1;
	uartRx.GPIO_Conf = In_PullUp;
	uartRx.GPIO_Pin = RxPin_UART1;
	MyGPIO_Init ( &uartRx );
	
	MyUSART_Init (&muart);
	MyUSART_Active_IT (&muart, USART_CallBack);
}
	

int main () {
  f2();
	while(1);
	

}
