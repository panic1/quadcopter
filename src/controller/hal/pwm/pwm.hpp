/*
 * pwm.hpp
 *
 *  Created on: 18-aug.-2016
 *      Author: nicky
 */

#ifndef HAL_PWM_PWM_HPP_
#define HAL_PWM_PWM_HPP_

#include <stdint.h>

class PWM
{
public:
	PWM(int pin_number);
	virtual ~PWM() {};

	virtual bool enable(void) = 0;
	virtual bool set_period_ns(uint32_t period) = 0;
	virtual bool set_duty_cycle_ns(uint32_t duty) = 0;

protected:
	int pin_number;
};


#endif /* HAL_PWM_PWM_HPP_ */
