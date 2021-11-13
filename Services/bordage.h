#ifndef BORDAGE_H
#define BORDAGE_H

//Initialisaiton du Timer en mode codeur incrémental
void bordage_Init_Codeur(void);

//Renvoie le rapport cyclique *100 en fonction de l'angle de la girouette (0-360)
int bordage_calcul_rapport_cyclique(int angle);

//Initialisation du servomoteur
void bordage_init_servo(void);

//Orientation du Servomoteur en fonction du RC
void bordage_Orienter_Servo(int duty_cycle);

//Retourne l'angle (TIM3 CH1 CNT)
int bordage_get_angle(void);
#endif
