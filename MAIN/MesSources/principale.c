#include "bordage.h"
#include "direction.h"
#include "Timing.h"
#include "MyTransmission.h"

static int i = 0;

void Ordonnancement (void) {
	bordage_Orienter_Servo(bordage_calcul_rapport_cyclique(bordage_get_angle()));
	if (i==300){
		MyTransmission_Send(bordage_get_angle());
		i =0;
	}
	i++;
}

int main(){
	bordage_Init_Codeur();
	bordage_init_servo();
	bordage_Orienter_Servo(bordage_calcul_rapport_cyclique(bordage_get_angle()));	
	direction_InitUart();
	MyTransmission_InitADCbat();
	MyTransmission_InitUart();
	Timing_Ordre(Ordonnancement);
	while(1);
}

