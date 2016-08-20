/*
 * pwm_beagleboneblack.hpp
 *
 *  Created on: 18-aug.-2016
 *      Author: nicky
 */

#ifndef HAL_PWM_PWM_BEAGLEBONEBLACK_HPP_
#define HAL_PWM_PWM_BEAGLEBONEBLACK_HPP_

#include "pwm.hpp"

#define PWM_MAX_PINS 4

class PWM_beagleboneblack: public PWM
{
public:
	PWM_beagleboneblack(int pin_number);
	virtual ~PWM_beagleboneblack();

	virtual bool enable(void);
	virtual bool set_period_ns(uint32_t period);
	virtual bool set_duty_cycle_ns(uint32_t duty);

private:
	bool search_pwmchip_number();
	bool config_pin(bool set_to_default = false);
	bool export_pwm();
	bool unexport_pwm();
	bool enable_pwm();
	bool disable_pwm();
	std::string get_base_pwmchip_folder();
	std::string get_base_pwmx_folder();

	int pwmchip_number;
	bool exported;
	bool enabled;

	uint32_t period_ns;
	uint32_t duty_cycle_ns;
};






#endif /* HAL_PWM_PWM_BEAGLEBONEBLACK_HPP_ */
