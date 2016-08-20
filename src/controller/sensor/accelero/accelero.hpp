/*
 * accelero.hpp
 *
 *  Created on: 20-aug.-2016
 *      Author: nicky
 */

#ifndef SENSOR_ACCELERO_ACCELERO_HPP_
#define SENSOR_ACCELERO_ACCELERO_HPP_

#include "sensor/sensor.hpp"

enum AcceleroType
{
	accel_ad_adxl345,
	accel_st_lsm303dlhc
};

class Accelero: public Sensor_XYZ
{
public:
	Accelero(SensorOrientation orientation);
	virtual ~Accelero() {};

	virtual bool initialize() = 0;
	virtual SensorData_XYZ get_readout() = 0;

	static Accelero* create_accelero(AcceleroType type);

protected:
	SensorOrientation orientation;
};


#endif /* SENSOR_ACCELERO_ACCELERO_HPP_ */
