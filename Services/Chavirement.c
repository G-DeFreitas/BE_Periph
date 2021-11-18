#include "MySPI.h"
#include "adxl.h"
#include "Chavirement.h"

static MySPI_Struct_TypeDef mspi;
static Axes_Struct_TypeDef Axes;


void Chavirement_InitSPI (void) {
	mspi.SPI=SPI1;
	MySPI_Init (&mspi);
}
	

int Chavirement_DetectDepassement (void) {

	int Zrep=0;
	Axes.X=0;
	Axes.Y=0;
	Axes.Z=0;

	//adxl_Transmit(0x0, 0, mspi);
	adxl_init(mspi);
	
	Axes = adxl_Receive(0x32, mspi);
	Zrep= Axes.Z;
	
	if (Zrep<90){
		return 0;
	}
	else
	{
		return 1;
	}
}
