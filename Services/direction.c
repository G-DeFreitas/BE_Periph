#include "direction.h"
#include "MyUSART.h"
#include "MyTimer.h"

static MyUART_Struct_TypeDef muart;
static MyGPIO_Struct_TypeDef servo;
static MyGPIO_Struct_TypeDef bitsens;
static MyGPIO_Struct_TypeDef uartTx;
static MyGPIO_Struct_TypeDef uartRx;
static MyTimer_Struct_TypeDef timServo;

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
		MyTimer_Set_DutyCycle(timServo.Timer, 1, monMess*100);
		MyTimer_Base_Start(timServo.Timer);
	}

	void direction_InitUart (){
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
	}
	
	void direction_Orienter_Bateau () {
	MyUSART_Active_IT (&muart, USART_CallBack);
}
