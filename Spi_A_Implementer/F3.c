#include "MySPI.h"
#include "bordage.h"

MySPI_Struct_TypeDef mspi;
Axes_Struct_TypeDef Axes;
int i=0;

void f3 () {
	
	mspi.SPI=SPI1;
	MySPI_Init (&mspi);
	
}
	

int main () {

	
	int Xrep=0;
	int Yrep=0;
	int Zrep=0;
  f3();
	Axes.X=0;
	Axes.Y=0;
	Axes.Z=0;

	//adxl_Transmit(0x0, 0, mspi);
	adxl_init(mspi);
	bordage_init_servo();
	
	Axes = adxl_Receive(0x32, mspi);
	Xrep= Axes.X;
	Yrep= Axes.Y;
	Zrep= Axes.Z;
	
	
	
	while(1){
	Axes = adxl_Receive(0x32, mspi);
	Xrep= Axes.X;
	Yrep= Axes.Y;
	Zrep= Axes.Z;
	
	if (Zrep<90)
		bordage_Orienter_Servo(0);
		
	while (i <10000){i++;}
	}

}
