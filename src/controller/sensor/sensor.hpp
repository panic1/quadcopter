/*
 * sensor.hpp
 *
 *  Created on: 20-aug.-2016
 *      Author: nicky
 */

#ifndef SENSOR_SENSOR_HPP_
#define SENSOR_SENSOR_HPP_

#include "sensordefs.hpp"

class Sensor
{
public:
	Sensor() {};
	virtual ~Sensor() {};
};

class Sensor_XYZ: public Sensor
{
public:
	Sensor_XYZ() {};
	virtual ~Sensor_XYZ() {};

	virtual SensorData_XYZ get_readout() = 0;
};


#endif /* SENSOR_SENSOR_HPP_ */
