/*
 * sensordefs.hpp
 *
 *  Created on: 20-aug.-2016
 *      Author: nicky
 */

#ifndef SENSOR_SENSORDEFS_HPP_
#define SENSOR_SENSORDEFS_HPP_

#include <stdint.h>


struct SensorData_XYZ
{
	SensorData_XYZ():
		X(0),
		Y(0),
		Z(0)
	{};

	int32_t X;
	int32_t Y;
	int32_t Z;
};

enum Direction
{
	forward,
	backward,
	downward,
	upward,
	right,
	left,
};

struct SensorOrientation
{
	Direction X_direction;
	Direction Y_direction;
	Direction Z_direction;
};


#endif /* SENSOR_SENSORDEFS_HPP_ */
