/*
 * gyro_st_l3g.cpp
 *
 *  Created on: 20-aug.-2016
 *      Author: nicky
 */

#include <iostream>
#include "gyro_st_l3g.hpp"


Gyro_St_L3g::Gyro_St_L3g(SensorOrientation orientation, I2C* i2c):
	Gyro(orientation),
	i2c(i2c)
{}

Gyro_St_L3g::~Gyro_St_L3g()
{}

bool Gyro_St_L3g::initialize()
{
	if( !i2c->open( O_RDWR | O_NONBLOCK ))
	{
		std::cerr << "Cannot open i2c device." << std::endl;
		return false;
	}

	// Turns on the L3G's gyro and places it in normal mode.
	// Normal power mode, all axes enabled (for detailed info see datasheet)
	i2c->write_byte(L3G_CTRL_REG2, 0x00); // highpass filter disabled
	i2c->write_byte(L3G_CTRL_REG3, 0x00);
	i2c->write_byte(L3G_CTRL_REG4, 0x20); // sets acuracy to 2000 dps (degree per second)
	i2c->write_byte(L3G_CTRL_REG5, 0x00); // deactivates the filters (only use one of these options)
	i2c->write_byte(L3G_CTRL_REG1, 0x0F); // starts Gyro measurement

	i2c->close();
	return true;
}

SensorData_XYZ Gyro_St_L3g::get_readout()
{
	uint8_t values[6];
	SensorData_XYZ data;

	if( !i2c->open( O_RDWR | O_NONBLOCK ))
	{
		std::cerr << "Cannot open i2c device." << std::endl;
		return SensorData_XYZ();
	}

	i2c->read_byte(L3G_OUT_X_L, values[0]);
	i2c->read_byte(L3G_OUT_X_H, values[1]);
	data.X = static_cast<int16_t>(static_cast<uint16_t>(values[0]) | (static_cast<uint16_t>(values[1]) << 8));
	i2c->read_byte(L3G_OUT_Y_L, values[2]);
	i2c->read_byte(L3G_OUT_Y_H, values[3]);
	data.Y = static_cast<int16_t>(static_cast<uint16_t>(values[2]) | (static_cast<uint16_t>(values[3]) << 8));
	i2c->read_byte(L3G_OUT_Z_L, values[4]);
	i2c->read_byte(L3G_OUT_Z_H, values[5]);
	data.Z = static_cast<int16_t>(static_cast<uint16_t>(values[4]) | (static_cast<uint16_t>(values[5]) << 8));

	i2c->close();
	return data;
}
