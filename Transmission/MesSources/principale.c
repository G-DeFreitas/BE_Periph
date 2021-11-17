#include "MyTransmission.h"
#include "MyUSART.h"

int main(){
	MyTransmission_InitADCbat();
	MyTransmission_InitUart();
	MyTransmission_Send(100);
	while(1);
}

