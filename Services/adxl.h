#ifndef _ADXL_H_
#define _ADXL_H_
#include "MySPI.h"
void adxl_Transmit (int address, int value, MySPI_Struct_TypeDef myspi);
Axes_Struct_TypeDef adxl_Receive (int address, MySPI_Struct_TypeDef myspi);
void adxl_init(MySPI_Struct_TypeDef mspi);
#endif
