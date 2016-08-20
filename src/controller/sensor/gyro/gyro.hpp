/*
 * gyro.hpp
 *
 *  Created on: 20-aug.-2016
 *      Author: nicky
 */

#ifndef SENSOR_GYRO_GYRO_HPP_
#define SENSOR_GYRO_GYRO_HPP_

#include "sensor/sensor.hpp"

enum GyroType
{
	gyro_st_l3g,
};

class Gyro: public Sensor_XYZ
{
public:
	Gyro(SensorOrientation orientation);
	virtual ~Gyro() {};

	virtual bool initialize() = 0;
	virtual SensorData_XYZ get_readout() = 0;

	static Gyro* create_gyro(GyroType type);

protected:
	SensorOrientation orientation;
};


#endif /* SENSOR_GYRO_GYRO_HPP_ */
