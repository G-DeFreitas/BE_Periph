#include "adxl.h"
#include "MySPI.h"

static signed int reponse1;
static signed int reponse2;
	
void adxl_Transmit (int address, int value)
{
	CS_Reset();
	
	//ecrire puis lire poubelle
	MySPI_Transmit(address);
	MySPI_Transmit(value);
	CS_Set();
}
/*write function
pull the CS low to enable the slave
transmit the address to which we want to write data
transmit the data
pull the CS pin high to disable the slave
*/

Axes_Struct_TypeDef adxl_Receive (int address)
{
	
	Axes_Struct_TypeDef Ang;
	
	//multibyte
	address |= (0xC0);

	CS_Reset();
	
	//ecrire poubelle
	MySPI_Transmit(address);
	
	//lire data x
	reponse1 = MySPI_Receive(0);
	reponse2 = MySPI_Receive(0);
	
	//if (reponse2 !=0 & reponse1 !=0) 
		Ang.X=reponse2+(reponse1<<8);
	
	//lire data y
	reponse1 = MySPI_Receive(0);
	reponse2 = MySPI_Receive(0);
	
	//if (reponse2 !=0 & reponse1 !=0) 
		Ang.Y=reponse2+(reponse1<<8);
	
	//lire data z
	reponse1 = MySPI_Receive(0);
	reponse2 = MySPI_Receive(0);
	
	if (reponse2 !=0 & reponse1 !=0) 
		Ang.Z=reponse1+(reponse2<<8);

	CS_Set();
	
	return Ang;
}
/*read function
pull the CS low to enable the slave
transmit the address from where we want to read data
receive data. 6 bytes in this case
pull the CS pin high to disable the slave 
*/



//initilisation du adxl 

void adxl_init(){
	adxl_Transmit(0x31, 0x01);  // data_format range= +- 4g
	adxl_Transmit(0x2d, 0x00);  // reset all bits
	adxl_Transmit(0x2d, 0x08);  // measure and wake up 8hz
}

/*
we need to modify POWER_CTL Register (0x2D) and DATA_FORMAT Register (0x31). 
RESET all bits of POWER_CTLby writing 0 to them
SET the MEASURE bit,
RESET the SLEEP bit
SET the frequency in the WAKE UP bits
DATA_FORMAT Register, Set the RANGE using D0 and D1
DEVID register (0x00)  holds a fixed device ID code of 0xE5 .
If the code matches 0xE5 ok
*/



