#ifndef BORDAGE_H
#define BORDAGE_H

//Initialisaiton du Timer en mode codeur incrémental
void bordage_Init_Codeur();

//Renvoie le rapport cyclique *100 en fonction de l'angle de la girouette (0-360)
int bordage_calcul_rapport_cyclique(int angle);

//Initialisation du servomoteur
void bordage_init_servo();

#endif
