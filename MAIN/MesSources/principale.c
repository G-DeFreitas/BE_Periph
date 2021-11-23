#include "bordage.h"
#include "direction.h"
#include "Timing.h"
#include "MyTransmission.h"
#include "Chavirement.h"
static int i = 0;
void Ordonnancement (void) {
	if ( Chavirement_DetectDepassement() == 1 ){
		bordage_Orienter_Servo(bordage_calcul_rapport_cyclique(bordage_get_angle()));
		if (i==300){
			MyTransmission_NormalSend(bordage_get_angle());
			i =0;
		}
	}
	else{
		//bordage_Orienter_Servo(bordage_calcul_rapport_cyclique(0));
		bordage_Orienter_Servo(0750);
		if (i==300){
			MyTransmission_AlertSend();
			i =0;
		}
	}
	i++;
}

int main(){
	bordage_Init_Codeur();
	bordage_init_servo();
	bordage_Orienter_Servo(bordage_calcul_rapport_cyclique(bordage_get_angle()));	
	direction_InitUart();
	Chavirement_InitSPI();
	direction_Orienter_Bateau();
	MyTransmission_InitADCbat();
	MyTransmission_InitUart();
	Timing_Ordre(Ordonnancement);
	while(1);
}

