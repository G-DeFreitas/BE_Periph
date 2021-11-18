#include "MySPI.h"

void MySPI_Init (MySPI_Struct_TypeDef * MySPI) {
	
	MyGPIO_Struct_TypeDef nss;
	MyGPIO_Struct_TypeDef mosi;
	MyGPIO_Struct_TypeDef miso;
	MyGPIO_Struct_TypeDef sclk;
	MyGPIO_Struct_TypeDef chipsel;
	
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
	
	//Selection de BR 
	MySPI->SPI->CR1  |= SPI_CR1_BR_0;
	MySPI->SPI->CR1 |= SPI_CR1_BR_1;
	MySPI->SPI->CR1 |= SPI_CR1_BR_2;
	
	//Selectionner CPOL et CPHA à 1
	MySPI->SPI->CR1 |=  SPI_CR1_CPOL;
	MySPI->SPI->CR1 |= SPI_CR1_CPHA ;
	
	//spe a zero pour cofig dff
	MySPI->SPI->CR1 &= ~SPI_CR1_SPE;
	
	//Set le bit DFF pour le format 8 bit 
	MySPI->SPI->CR1 &= ~(SPI_CR1_DFF);
	
	// bit LSBFIRST dans CR1 pour le format, transmet le MSB en premier
	MySPI->SPI->CR1 &= ~(SPI_CR1_LSBFIRST);
	
	
	//NSS
	MySPI->SPI->CR1 |= SPI_CR1_SSM;
	MySPI->SPI->CR1 |= SPI_CR1_SSI;
	
	// RXONLY = 0, full-duplex
	MySPI->SPI->CR1 &= ~SPI_CR1_RXONLY;
	
	//MSTR et SPE à 1
	MySPI->SPI->CR1 |= SPI_CR1_MSTR;
	MySPI->SPI->CR1 |= SPI_CR1_SPE;
	
	MySPI->SPI->CR2 = 0;
	//Config GPIO
	
	//pin MISO en GPIO input
	miso.GPIO = GPIO_SPI1;
	miso.GPIO_Conf = In_PullUp;
	miso.GPIO_Pin = MISOPin_SPI1;
	MyGPIO_Init ( &miso );
	
	//pin MOSI en GPIO input

	mosi.GPIO = GPIO_SPI1;
	mosi.GPIO_Conf = AltOut_Ppull;
	mosi.GPIO_Pin = MOSIPin_SPI1;
	MyGPIO_Init ( &mosi );

	//pin NSS en Output Push-pull
	
	nss.GPIO = GPIO_SPI1;
	nss.GPIO_Conf = Out_Ppull;
	nss.GPIO_Pin = nssPin_SPI1;
	MyGPIO_Init ( &nss );
	
	//Init clock
	sclk.GPIO = GPIO_SPI1;
	sclk.GPIO_Conf = AltOut_Ppull;
	sclk.GPIO_Pin = sckPin_SPI1;
	MyGPIO_Init ( &sclk );
	
	//Chip select
	chipsel.GPIO = GPIO_SPI1;
	chipsel.GPIO_Conf = Out_Ppull;
	chipsel.GPIO_Pin = chipselPin_SPI1;
	MyGPIO_Init ( &chipsel );
	
	CS_Set();
}

char MySPI_ReadWrite(int toSend, MySPI_Struct_TypeDef * MySPI) {
	//Voir page 743
	//On récupère la valeur du flag TXE

	//On attend qu'il soit vide pour attribuer la valeur toSend à DR
	while ( (MySPI->SPI->SR & SPI_SR_TXE)==0){}
	MySPI->SPI->DR = toSend;
	
	//On attend qu'il soit plein pour lire
	while (!(MySPI->SPI->SR & SPI_SR_RXNE)){}
	return MySPI->SPI->DR;
}

void SPI_Enable (MySPI_Struct_TypeDef * MySPI)
{    MySPI->SPI->CR1 |= (SPI_CR1_SPE);   // SPE=1, Peripheral enabled
}

void SPI_Disable (MySPI_Struct_TypeDef * MySPI)
{		MySPI->SPI->CR1 &= ~(SPI_CR1_SPE);   // SPE=0, Peripheral Disabled
}

void CS_Set (void) //pin SPI1_CS PA11
{   
			MyGPIO_Set(GPIO_SPI1 , chipselPin_SPI1 ) ;
}

void CS_Reset (void)
{    
			MyGPIO_Reset(GPIO_SPI1 , chipselPin_SPI1 ) ;
}
