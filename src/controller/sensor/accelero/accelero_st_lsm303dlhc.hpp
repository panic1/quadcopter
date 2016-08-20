/*
 * accelero_st_lsm303dlhc.hpp
 *
 *  Created on: 20-aug.-2016
 *      Author: nicky
 */

#ifndef SENSOR_ACCELERO_ACCELERO_ST_LSM303DLHC_HPP_
#define SENSOR_ACCELERO_ACCELERO_ST_LSM303DLHC_HPP_

#include "accelero.hpp"
#include "hal/i2c/i2c.hpp"

#define LSM303DLHC_CTRL_REG1		0x20
#define LSM303DLHC_CTRL_REG2		0x21
#define LSM303DLHC_CTRL_REG3		0x22
#define LSM303DLHC_CTRL_REG4		0x23
#define LSM303DLHC_CTRL_REG5		0x24
#define LSM303DLHC_CTRL_REG6		0x25
#define LSM303DLHC_REFERENCE		0x26
#define LSM303DLHC_STATUS_REG 		0x27
#define LSM303DLHC_OUT_X_L			0x28
#define LSM303DLHC_OUT_X_H			0x29
#define LSM303DLHC_OUT_Y_L			0x2A
#define LSM303DLHC_OUT_Y_H			0x2B
#define LSM303DLHC_OUT_Z_L			0x2C
#define LSM303DLHC_OUT_Z_H			0x2D
#define LSM303DLHC_FIFO_CTRL_REG	0x2E
#define LSM303DLHC_FIFO_SRC_REG		0x2F
#define LSM303DLHC_INT1_CFG			0x30
#define LSM303DLHC_INT1_SOURCE		0x31
#define LSM303DLHC_INT1_THS			0x32
#define LSM303DLHC_INT1_DURATION	0x33
#define LSM303DLHC_INT2_CFG			0x34
#define LSM303DLHC_INT2_SOURCE		0x35
#define LSM303DLHC_INT2_THS			0x36
#define LSM303DLHC_INT2_DURATION	0x37
#define LSM303DLHC_CLICK_CFG		0x38
#define LSM303DLHC_CLICK_SRC		0x39
#define LSM303DLHC_CLICK_THS		0x3A
#define LSM303DLHC_TIME_LIMIT		0x3B
#define LSM303DLHC_TIME_LATENCY		0x3C
#define LSM303DLHC_TIME_WINDOW		0x3D

class Accelero_St_Lsm303dlhc: public Accelero
{
public:
	Accelero_St_Lsm303dlhc(SensorOrientation orientation, I2C* i2c);
	virtual ~Accelero_St_Lsm303dlhc();

	bool initialize();
	SensorData_XYZ get_readout();

private:
	I2C* i2c;
};


#endif /* SENSOR_ACCELERO_ACCELERO_ST_LSM303DLHC_HPP_ */
