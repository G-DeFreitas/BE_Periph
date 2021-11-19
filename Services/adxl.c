#include "adxl.h"
#include "MySPI.h"

static int reponse1;
static int reponse2;
	
void adxl_Transmit (int address, int value, MySPI_Struct_TypeDef myspi)
{
	CS_Reset();
	
	//ecrire puis lire poubelle
	MySPI_ReadWrite(address, &myspi);
	MySPI_ReadWrite(value, &myspi);
	CS_Set();
}
/*write function
pull the CS low to enable the slave
transmit the address to which we want to write data
transmit the data
pull the CS pin high to disable the slave
*/

Axes_Struct_TypeDef adxl_Receive (int address, MySPI_Struct_TypeDef myspi)
{
	
	Axes_Struct_TypeDef Ang;
	
	
	address |= (0xC0);

	CS_Reset();
	//ecrire poubelle
	MySPI_ReadWrite(address, &myspi);
//	MySPI_ReadWrite(0xAA, &myspi);
	
	//lire data x
	reponse1 = MySPI_ReadWrite(0, &myspi);
	reponse2 = MySPI_ReadWrite(0, &myspi);
	
	//if (reponse2 !=0 & reponse1 !=0) 
		Ang.X=reponse1+(reponse2<<8);
	
	//lire data y
	reponse1 = MySPI_ReadWrite(0, &myspi);
	reponse2 = MySPI_ReadWrite(0, &myspi);
	
	//if (reponse2 !=0 & reponse1 !=0) 
		Ang.Y=reponse1+(reponse2<<8);
	
	//lire data z
	reponse1 = MySPI_ReadWrite(0, &myspi);
	reponse2 = MySPI_ReadWrite(0, &myspi);
	
	//if (reponse2 !=0 & reponse1 !=0) 
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

void adxl_init(MySPI_Struct_TypeDef mspi){
	adxl_Transmit(0x2d, 0x00, mspi);  // reset all bits
	adxl_Transmit(0x2d, 0x08, mspi);  // measure and wake up 8hz
	adxl_Transmit(0x31, 0x01, mspi);  // data_format range= +- 4g

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



