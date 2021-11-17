#include "MyTransmission.h"
#include "direction.h"
#include "MyUSART.h"

MyUART_Struct_TypeDef MyUart;
static const char msg[] = "8=======D";
int i;

int main(){
	MyUart.Uart = USART1;
	MyUart.Debit = 9600;
	MyUart.Prio = 4;
MyTransmission_InitADCbat();
	MyUSART_Init (&MyUart);
	for (i=0; i<9;i++){
	MyUSART_Send_Byte(MyUart.Uart, msg[i]);
	while((MyUart.Uart->SR & USART_SR_TXE) ==0);
	}
	while(1);

}

