#include "bordage.h"
#include "direction.h"
#include "Timing.h"

void Ordonnacement (void) {
	bordage_Orienter_Servo(bordage_calcul_rapport_cyclique(bordage_get_angle()));
}

int main(){
	bordage_Init_Codeur();
	bordage_init_servo();
	bordage_Orienter_Servo(bordage_calcul_rapport_cyclique(bordage_get_angle()));	
	direction_InitUart();
	direction_Orienter_Bateau();
	Timing_Ordre(Ordonnacement);

	while(1);
}

