#ifndef _ADXL_H_
#define _ADXL_H_
#include "MySPI.h"
void adxl_Transmit (int address, int value);
Axes_Struct_TypeDef adxl_Receive (int address);
void adxl_init(void);
#endif
