/*
 * main.cpp
 *
 *  Created on: Nov 28, 2014
 *      Author: Nicky Geerts
 */

#include <iostream>
#include <iomanip>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>

#include "sensor/gyro/gyro.hpp"
#include "sensor/accelero/accelero.hpp"

#include "hal/pwm/pwm_beagleboneblack.hpp"
#include "hal/i2c/i2c.hpp"

using namespace std;

void test_pwm();
void test_i2c();

int main(void)
{
	// TODO read configuration file

	// create sensors
	Gyro* gyro = Gyro::create_gyro(gyro_st_l3g);


	while(true)
	{
		usleep(100000);

		SensorData_XYZ data = gyro->get_readout();
    	std::cout << "Gyro ==> X value: " << setw(10) << data.X << " Y value: " << setw(10) << data.Y << " Z value: " << setw(10) << data.Z << std::endl;
	}
	return 0;
}

void test_pwm()
{
	PWM* myPwm1 = new PWM_beagleboneblack(0);
	PWM* myPwm2 = new PWM_beagleboneblack(1);
	PWM* myPwm3 = new PWM_beagleboneblack(2);
	PWM* myPwm4 = new PWM_beagleboneblack(3);

	myPwm1->enable();
	myPwm2->enable();
	myPwm3->enable();
	myPwm4->enable();

	myPwm1->set_period_ns(20000000);
	myPwm2->set_period_ns(20000000);
	myPwm3->set_period_ns(20000000);
	myPwm4->set_period_ns(20000000);

	int duty_cycle = 1000000;
	myPwm1->set_duty_cycle_ns(duty_cycle);
	myPwm2->set_duty_cycle_ns(duty_cycle);
	myPwm3->set_duty_cycle_ns(duty_cycle);
	myPwm4->set_duty_cycle_ns(duty_cycle);

	sleep(5);
	while (true)
	{
		usleep(100000);

		duty_cycle += 1000;
		if (duty_cycle >= 1300000) duty_cycle = 1000000;

		std::cout << "Duty Cycle: " << duty_cycle << std::endl;

		myPwm1->set_duty_cycle_ns(duty_cycle);
		myPwm2->set_duty_cycle_ns(duty_cycle);
		myPwm3->set_duty_cycle_ns(duty_cycle);
		myPwm4->set_duty_cycle_ns(duty_cycle);
	}
}

void test_i2c_accelerometer_nicky()
{
    I2C  myI2c(2, 0x53);
    if( !myI2c.open( O_RDWR  | O_NONBLOCK ))
    {
        std::cout << "I2C DEVICE CAN\'T OPEN.;" << std::endl;
        exit(1);
    }

    // read-write register
    uint8_t powerCtl_Addr   = 0x2D;
    uint8_t dataformat_Addr = 0x31;
//    uint8_t offsetX_Addr    = 0x1E;
//    uint8_t offsetY_Addr    = 0x1F;
//    uint8_t offsetZ_Addr    = 0x20;

    // read only register
    uint8_t axisX0_Addr     = 0x32;
//    uint8_t axisX1_Addr     = 0x33;
//    uint8_t axisY0_Addr     = 0x34;
//    uint8_t axisY1_Addr     = 0x35;
//    uint8_t axisZ0_Addr     = 0x36;
//    uint8_t axisZ1_Addr     = 0x37;

    // set bit
    uint8_t measureMode     = 0x08;

    uint8_t powerCtlReg;
    myI2c.read_byte(powerCtl_Addr, powerCtlReg);
    std::cout << "Power Ctrl's current value: " << std::hex << (int)powerCtlReg << std::dec << std::endl;

    powerCtlReg |= (measureMode);      //                      ___ ___ ___ ___|___ ___ ___ ___
                                       // powerCtlReg:        |_x_|_x_|_x_|_x_|_x_|_x_|_x_|_x_|
                                       // measureMode:        |_0_|_0_|_0_|_0_|_1_|_0_|_0_|_0_|
                                       //                      ___ ___ ___ ___|___ ___ ___ ___ or these
                                       // result:             |_x_|_x_|_x_|_x_|_1_|_x_|_x_|_x_|

    myI2c.write_byte(powerCtl_Addr, powerCtlReg);

    std::cout << "Power Ctrl's new value: " << std::hex << (int)powerCtlReg << std::dec << std::endl;


    uint8_t fullresMode		= 0x08;

    uint8_t dataformatReg;
    myI2c.read_byte(dataformat_Addr, dataformatReg);
    std::cout << "data format's current value: " << std::hex << (int)dataformatReg << std::dec << std::endl;

    dataformatReg |= fullresMode;
    myI2c.write_byte(dataformat_Addr, dataformatReg);

    std::cout << "data format's new value: " << std::hex << (int)dataformatReg << std::dec << std::endl;


    uint8_t values[6];

    while (true)
    {
    	myI2c.read_block(axisX0_Addr, values, sizeof(values));

    	int X = static_cast<int16_t>(static_cast<uint16_t>(values[0]) | (static_cast<uint16_t>(values[1]) << 8));
    	int Y = static_cast<int16_t>(static_cast<uint16_t>(values[2]) | (static_cast<uint16_t>(values[3]) << 8));
    	int Z = static_cast<int16_t>(static_cast<uint16_t>(values[4]) | (static_cast<uint16_t>(values[5]) << 8));

    	std::cout << "X value: " << setw(10)<< X << " Y value: " << setw(10)<< Y << " Z value: " << setw(10)<< Z << std::endl;
    	usleep(20000);
    }
}



void test_i2c_accelerometer_kris()
{
    I2C  myI2c(2, 0x19);
    bool isOpened = myI2c.open( O_RDWR | O_NONBLOCK );
    if( !isOpened )
    {
        std::cout << "I2C DEVICE CAN\'T OPEN.;" << std::endl;
        exit(1);
    }

    // CTRL_REG1_A (20h)
    // CTRL_REG1_A register ODR3 ODR2 ODR1 ODR0 LPen Zen Yen Xen
/*
 * ODR3-0
Data rate selection. Default value: 0 (0000: power-down, others: refer to Table 20.)
LPen
Low-power mode enable. Default value: 0 (0: normal mode, 1: low-power mode)
Zen
Z axis enable. Default value: 1 (0: Z axis disabled, 1: Z axis enabled)
Yen
Y axis enable. Default value: 1 (0: Y axis disabled, 1: Y axis enabled)
Xen
X axis enable. Default value: 1 (0: X axis disabled, 1: X axis enabled)
 */

    /*
     *ODR3 ODR2 ODR1 ODR0 Power mode selection
0 0 0 0 Power-down mode 0 0 0 1 Normal / low-power mode (1 Hz) 0 0 1 0 Normal / low-power mode (10 Hz) 0 0 1 1 Normal / low-power mode (25 Hz) 0 1 0 0 Normal / low-power mode (50 Hz) 0 1 0 1 Normal / low-power mode (100 Hz) 0 1 1 0 Normal / low-power mode (200 Hz) 0 1 1 1 Normal / low-power mode (400 Hz) 1 0 0 0 Low-power mode (1.620 KHz) 1 0 0 1 Normal (1.344 kHz) / low-power mode (5.376 KHz)
     */
    uint CTRL_REG1_Addr = 0x20;

    uint8_t regCtlReg;
    myI2c.read_byte(CTRL_REG1_Addr, regCtlReg);
        std::cout << "Power Ctrl's current value: " << std::hex << (int)regCtlReg << std::dec << std::endl;
    uint8_t mode     = 0x47;
    myI2c.write_byte(CTRL_REG1_Addr, mode);

    myI2c.write_byte(0x23, 0x58);

    //check reg_statsu STATUS_REG_A (27h) ZYXOR ZOR YOR XOR ZYXDA ZDA YDA XDA
/*	ZYXOR X, Y, and Z axis data overrun. Default value: 0 (0: no overrun has occurred, 1: a new set of data has overwritten the previous ones)
 *  ZOR Z axis data overrun. Default value: 0 (0: no overrun has occurred, 1: a new data for the Z-axis has overwritten the previous one)
 *  YOR Y axis data overrun. Default value: 0 (0: no overrun has occurred, 1: a new data for the Y-axis has overwritten the previous one)
 *  XOR X axis data overrun. Default value: 0 (0: no overrun has occurred, 1: a new data for the X-axis has overwritten the previous one)
 *  ZYXDA X, Y, and Z axis new data available. Default value: 0 (0: a new set of data is not yet available, 1: a new set of data is available)
 *  ZDA Z axis new data available. Default value: 0 (0: a new data for the Z-axis is not yet available, 1: a new data for the Z-axis is available)
 *  YDA Y axis new data available. Default value: 0 (0: a new data for the Y-axis is not yet available, 1: a new data for the Y-axis is available)
 *  XDA X axis new data available. Default value: 0 (0: a new data for the X-axis is not yet available, 1: a new data for the X-axis is available)*/
    int StatusReg_Addr = 0x27;
    uint8_t statusReg;
    myI2c.read_byte(StatusReg_Addr, statusReg);


    // read-write register
//    uint8_t powerCtl_Addr   = 0x2D;
//    uint8_t offsetX_Addr    = 0x1E;
//    uint8_t offsetY_Addr    = 0x1F;
//    uint8_t offsetZ_Addr    = 0x20;

    // read only register
    uint8_t axisX0_Addr     = 0x28;
//    OUT_X_L_A (28h), OUT_X_H_A (29h)
//    OUT_Y_L_A (2Ah), OUT_Y_H_A (2Bh)
//	  OUT_Z_L_A (2Ch), OUT_Z_H_A (2Dh)

//	uint8_t axisX0_Addr     = 0x32;
//    uint8_t axisX1_Addr     = 0x33;
//    uint8_t axisY0_Addr     = 0x34;
//    uint8_t axisY1_Addr     = 0x35;
//    uint8_t axisZ0_Addr     = 0x36;
//    uint8_t axisZ1_Addr     = 0x37;

    // set bit
//    uint8_t measureMode     = 0x08;

//    uint8_t powerCtlReg     = myI2c.readByte(powerCtl_Addr);
//    std::cout << "Power Ctrl's current value: " << std::hex << (int)powerCtlReg << std::dec << std::endl;

//    powerCtlReg |= (measureMode);      //                      ___ ___ ___ ___|___ ___ ___ ___
                                       // powerCtlReg:        |_x_|_x_|_x_|_x_|_x_|_x_|_x_|_x_|
                                       // measureMode:        |_0_|_0_|_0_|_0_|_1_|_0_|_0_|_0_|
                                       //                      ___ ___ ___ ___|___ ___ ___ ___ or these
                                       // result:             |_x_|_x_|_x_|_x_|_1_|_x_|_x_|_x_|

//    myI2c.writeByte(powerCtl_Addr, powerCtlReg);

//    std::cout << "Power Ctrl's new value: " << std::hex << (int)powerCtlReg << std::dec << std::endl;

    uint8_t values[6];

    while (true)
    {
    	// BLCVOK READ DOES NOT WORK ON YETI'S BEAGLE SENSOR
    	//myI2c.readBlock(axisX0_Addr, values, sizeof(values));

    	myI2c.read_byte(axisX0_Addr+0, values[0]);
    	myI2c.read_byte(axisX0_Addr+1, values[1]);
    	myI2c.read_byte(axisX0_Addr+2, values[2]);
    	myI2c.read_byte(axisX0_Addr+3, values[3]);
    	myI2c.read_byte(axisX0_Addr+4, values[4]);
    	myI2c.read_byte(axisX0_Addr+5, values[5]);
    	std::cout << "Values afzonderlijk: " << setw(5) << (int)values[0] << " "<< setw(5) << (int)values[1] << " " << setw(5) << (int)values[2] << " " << setw(5) << (int)values[3] << " "<< setw(5)<< (int)values[4] << " "<< setw(5) << (int)values[5] << std::endl;

    	int X = static_cast<int16_t>(static_cast<uint16_t>(values[1]) | (static_cast<uint16_t>(values[0]) << 8));
    	int Y = static_cast<int16_t>(static_cast<uint16_t>(values[3]) | (static_cast<uint16_t>(values[2]) << 8));
    	int Z = static_cast<int16_t>(static_cast<uint16_t>(values[5]) | (static_cast<uint16_t>(values[4]) << 8));

    	std::cout << "X  value: " << setw(10)<< X  << " Y  value: " << setw(10)<< Y  << " Z  value: " << setw(10)<< Z << ""<<std::endl;

    	usleep(20000);
    }


}

void test_i2c()
{
	test_i2c_accelerometer_nicky();
//	test_i2c_accelerometer_kris();
}

