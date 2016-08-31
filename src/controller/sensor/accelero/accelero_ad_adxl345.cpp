/*
 * accelero_ad_adxl345.cpp
 *
 *  Created on: 20-aug.-2016
 *      Author: nicky
 */

#include <iostream>
#include <stdlib.h>
#include "accelero_ad_adxl345.hpp"

Accelero_Ad_Adxl345::Accelero_Ad_Adxl345(SensorOrientation orientation, I2C* i2c):
	Accelero(orientation),
	i2c(i2c)
{}

Accelero_Ad_Adxl345::~Accelero_Ad_Adxl345()
{
	free(i2c);
	i2c = NULL;
}

bool Accelero_Ad_Adxl345::initialize()
{
	if( !i2c || !i2c->open( O_RDWR | O_NONBLOCK ))
	{
		std::cerr << "Cannot open i2c device." << std::endl;
		return false;
	}

	i2c->write_byte(ADXL345_POWER_CTL, 0x08);    // enable measure mode
	i2c->write_byte(ADXL345_DATA_FORMAT, 0x08);  // enable fullres mode, range 2G

	i2c->close();
	return true;
}

SensorData_XYZ Accelero_Ad_Adxl345::get_readout()
{
	uint8_t values[6];
	SensorData_XYZ data;

	if( !i2c || !i2c->open( O_RDWR | O_NONBLOCK ))
	{
		std::cerr << "Cannot open i2c device." << std::endl;
		return SensorData_XYZ();
	}

	i2c->read_block(ADXL345_DATAX0, values, sizeof(values));

	data.X = static_cast<int16_t>(static_cast<uint16_t>(values[0]) | (static_cast<uint16_t>(values[1]) << 8));
	data.Y = static_cast<int16_t>(static_cast<uint16_t>(values[2]) | (static_cast<uint16_t>(values[3]) << 8));
	data.Z = static_cast<int16_t>(static_cast<uint16_t>(values[4]) | (static_cast<uint16_t>(values[5]) << 8));

	i2c->close();
	return data;
}
