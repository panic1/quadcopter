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
	gyro->initialize();
	Accelero* accel_nicky = Accelero::create_accelero(accel_ad_adxl345);
	accel_nicky->initialize();
//	Accelero* accel_kris  = Accelero::create_accelero(accel_st_lsm303dlhc);
//	accel_kris->initialize();

	SensorData_XYZ data;
	while(true)
	{
		usleep(100000);

		data = gyro->get_readout();
    	std::cout << "Gyro     ==> X value: " << setw(10) << data.X << " Y value: " << setw(10) << data.Y << " Z value: " << setw(10) << data.Z << std::endl;

    	data = accel_nicky->get_readout();
//    	data = accel_kris->get_readout();
    	std::cout << "Accelero ==> X value: " << setw(10) << data.X << " Y value: " << setw(10) << data.Y << " Z value: " << setw(10) << data.Z << std::endl;
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

