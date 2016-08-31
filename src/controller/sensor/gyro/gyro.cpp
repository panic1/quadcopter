/*
 * gyro.cpp
 *
 *  Created on: 20-aug.-2016
 *      Author: nicky
 */

#include <cstdlib>
#include <iostream>
#include "hal/i2c/i2c.hpp"
#include "gyro.hpp"
#include "gyro_st_l3g.hpp"

Gyro::Gyro(SensorOrientation orientation):
	orientation(orientation)
{}


/*static*/
Gyro* Gyro::create_gyro(GyroType type)
{
	Gyro* gyro = NULL;
	switch (type)
	{
	case gyro_st_l3g:
		gyro = new Gyro_St_L3g(SensorOrientation(), new I2C(2, 0x69));  // nicky
//		gyro = new Gyro_St_L3g(SensorOrientation(), new I2C(2, 0x6B));  // kris
		break;
	default:
		std::cerr << "Unknown type of gyro requested." << std::endl;
	}

	return gyro;
}
