#include "bordage.h"

//// TEST DE LA COMMANDE DU SERVO
#include "MyTimer.h"
static MyTimer_Struct_TypeDef MonTimer;
void Interruption (void) {
	bordage_Orienter_Servo(bordage_calcul_rapport_cyclique(bordage_get_angle()));
}




int main(){
	bordage_Init_Codeur();
	bordage_init_servo();
	bordage_Orienter_Servo(bordage_calcul_rapport_cyclique(bordage_get_angle()));	
	
	//// TEST DE LA COMMANDE DU SERVO
	MonTimer.ARR = 10000-1;
	MonTimer.PSC = 72-1;
	MonTimer.Timer = TIM3;
	MyTimer_Base_Init(&MonTimer);
	MyTimer_ActiveIT(TIM3,3,Interruption);
	MyTimer_Base_Start (TIM3);




	while(1);
}

