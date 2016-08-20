/*
 * accelero_st_lsm303dlhs.cpp
 *
 *  Created on: 20-aug.-2016
 *      Author: nicky
 */

#include <iostream>
#include <stdlib.h>
#include "accelero_st_lsm303dlhc.hpp"

Accelero_St_Lsm303dlhc::Accelero_St_Lsm303dlhc(SensorOrientation orientation, I2C* i2c):
	Accelero(orientation),
	i2c(i2c)
{}

Accelero_St_Lsm303dlhc::~Accelero_St_Lsm303dlhc()
{
	free (i2c);
	i2c = NULL;
}

bool Accelero_St_Lsm303dlhc::initialize()
{
	if( !i2c || !i2c->open( O_RDWR | O_NONBLOCK ))
	{
		std::cerr << "Cannot open i2c device." << std::endl;
		return false;
	}

	i2c->write_byte(LSM303DLHC_CTRL_REG1, 0x47);  // power mode selection: 100Hz, enable x,y,z in normal power mode
	i2c->write_byte(LSM303DLHC_CTRL_REG4, 0x58);  // big endian mode, 4g mode, high res enable

	i2c->close();
	return true;
}

SensorData_XYZ Accelero_St_Lsm303dlhc::get_readout()
{
	uint8_t values[6];
	SensorData_XYZ data;

	if( !i2c || !i2c->open( O_RDWR | O_NONBLOCK ))
	{
		std::cerr << "Cannot open i2c device." << std::endl;
		return SensorData_XYZ();
	}
	i2c->read_byte(LSM303DLHC_OUT_X_L, values[0]);
	i2c->read_byte(LSM303DLHC_OUT_X_H, values[1]);
	i2c->read_byte(LSM303DLHC_OUT_Y_L, values[2]);
	i2c->read_byte(LSM303DLHC_OUT_Y_H, values[3]);
	i2c->read_byte(LSM303DLHC_OUT_Z_L, values[4]);
	i2c->read_byte(LSM303DLHC_OUT_Z_H, values[5]);

	data.X = static_cast<int16_t>(static_cast<uint16_t>(values[1]) | (static_cast<uint16_t>(values[0]) << 8));
	data.Y = static_cast<int16_t>(static_cast<uint16_t>(values[3]) | (static_cast<uint16_t>(values[2]) << 8));
	data.Z = static_cast<int16_t>(static_cast<uint16_t>(values[5]) | (static_cast<uint16_t>(values[4]) << 8));

	i2c->close();
	return data;
}
