/*
 * accelero_ad_adxl345.hpp
 *
 *  Created on: 20-aug.-2016
 *      Author: nicky
 */

#ifndef SENSOR_ACCELERO_ACCELERO_AD_ADXL345_HPP_
#define SENSOR_ACCELERO_ACCELERO_AD_ADXL345_HPP_

#include "accelero.hpp"
#include "hal/i2c/i2c.hpp"

#define ADXL345_DEVID			0x00  // Device ID
#define ADXL345_THRESH_TAP		0x1D  // Tap threshold
#define ADXL345_OFFSET_X		0x1E  // X-axis offset
#define ADXL345_OFFSET_Y		0x1F  // Y-axis offset
#define ADXL345_OFFSET_Z		0x20  // Z-axis offset
#define ADXL345_DUR				0x21  // Tap duration
#define ADXL345_LATENT			0x22  // Tap latency
#define ADXL345_WINDOW			0x23  // Tap window
#define ADXL345_THRESH_ACT		0x24  // Activity threshold
#define ADXL345_THRESH_INACT	0x25  // Inactivity threshold
#define ADXL345_TIME_INACT		0x26  // Inactivity time
#define ADXL345_ACT_INACT_CTL	0x27  // Axis enable control for activity and inactivity detection
#define ADXL345_THRESH_FF		0x28  // Free fall threshold
#define ADXL345_TIME_FF			0x29  // Free fall time
#define ADXL345_TAP_AXES		0x2A  // Axis control for single tap/double tap
#define ADXL345_ACT_TAP_STATUS	0x2B  // Source of single tap/double tap
#define ADXL345_BW_RATE			0x2C  // Data rate and power control mode
#define ADXL345_POWER_CTL		0x2D  // Power-saving features control
#define ADXL345_INT_ENABLE		0x2E  // Interrupt enable control
#define ADXL345_INT_MAP			0x2F  // Interrupt mapping control
#define ADXL345_INT_SOURCE		0x30  // Source of interrupts
#define ADXL345_DATA_FORMAT		0x31  // Data format control
#define ADXL345_DATAX0			0x32  // X-Axis Data 0
#define ADXL345_DATAX1			0x33  // X-Axis Data 1
#define ADXL345_DATAY0			0x34  // Y-Axis Data 0
#define ADXL345_DATAY1			0x35  // Y-Axis Data 1
#define ADXL345_DATAZ0			0x36  // Z-Axis Data 0
#define ADXL345_DATAZ1			0x37  // Z-Axis Data 1
#define ADXL345_FIFO_CTL		0x38  // FIFO control
#define ADXL345_FIFO_STATUS		0x39  // FIFO status

class Accelero_Ad_Adxl345: public Accelero
{
public:
	Accelero_Ad_Adxl345(SensorOrientation orientation, I2C* i2c);
	virtual ~Accelero_Ad_Adxl345();

	bool initialize();
	SensorData_XYZ get_readout();

private:
	I2C* i2c;

};



#endif /* SENSOR_ACCELERO_ACCELERO_AD_ADXL345_HPP_ */
