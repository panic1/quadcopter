/*
 * accelero.cpp
 *
 *  Created on: 20-aug.-2016
 *      Author: nicky
 */

#include <iostream>
#include "accelero.hpp"
#include "accelero_ad_adxl345.hpp"
#include "accelero_st_lsm303dlhc.hpp"

Accelero::Accelero(SensorOrientation orientation):
	orientation(orientation)
{}

/*static*/
Accelero* Accelero::create_accelero(AcceleroType type)
{
	Accelero* accel = NULL;
	switch (type)
	{
	case accel_ad_adxl345:
		accel = new Accelero_Ad_Adxl345(SensorOrientation(), new I2C(2, 0x53));
		break;
	case accel_st_lsm303dlhc:
		accel = new Accelero_St_Lsm303dlhc(SensorOrientation(), new I2C(2, 0x19));
		break;
	default:
		std::cerr << "Unknown type of aceclero requested." << std::endl;
	}

	return accel;
}
