// Fonction4 Transmission Info
#ifndef _MYTRANSMISSION_H
#define _MYTRANSMISSION_H


//Init l'Adc pour le niveau de batterie
void MyTransmission_InitADCbat(void);
//Renvoie le niveau de la batterie
//RefBatFaible 5, 10, 15 ...  100
//Renvoie 0 si Batterie "pleine" et 1 si batterie faible
int BatterieFaible(char RefBatFaible);


#endif
