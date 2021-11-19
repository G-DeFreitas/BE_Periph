#include "MySPI.h"
#include "adxl.h"
#include "Chavirement.h"

static MySPI_Struct_TypeDef mspi;
static Axes_Struct_TypeDef Axes;

void Chavirement_InitSPI (void) {
	mspi.SPI=SPI1;
	MySPI_Init (&mspi);
		adxl_init(mspi);
}
	

int Chavirement_DetectDepassement (void) {

	Axes = adxl_Receive(0x32, mspi);
	return Axes.Z;
}
