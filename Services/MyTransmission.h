// Fonction4 Transmission Info
#ifndef _MYTRANSMISSION_H
#define _MYTRANSMISSION_H
#include "MyUSART.h"

//Init l'Adc pour le niveau de batterie
void MyTransmission_InitADCbat(void);
//Renvoie le niveau de la batterie
//RefBatFaible 5, 10, 15 ...  100 (pourcentage de la batterie)
//Renvoie 0 si Batterie "pleine" et 1 si batterie faible
int MyTransmission_BatterieFaible(char RefBatFaible);

void MyTransmission_InitUart(void);
void MyTransmission_NormalSend(int angle);
void MyTransmission_AlertSend(void);
#endif
