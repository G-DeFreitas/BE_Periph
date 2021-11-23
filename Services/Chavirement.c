#include "MySPI.h"
#include "adxl.h"
#include "Chavirement.h"

static Axes_Struct_TypeDef Axes;

void Chavirement_InitSPI (void) {
	MySPI_Init ();
	adxl_init();
}
	

int Chavirement_DetectDepassement (void) {
	int res;

	Axes = adxl_Receive(0x32);
	Axes.Y = (Axes.Y)*0.78;
	Axes.X = (Axes.X)*0.78;
	Axes.Z = (Axes.Z)*0.78;
	

	if ((Axes.Y>40000) || (Axes.Y>=0 && Axes.Y < 10000))
		res = 1;
	else
		res =0;
	return res;
}
