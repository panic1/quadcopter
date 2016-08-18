/*
 * pwm_beagleboneblack.cpp
 *
 *  Created on: 18-aug.-2016
 *      Author: nicky
 */

#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <dirent.h>
#include "pwm_beagleboneblack.hpp"


struct {
	uint32_t 	chipset_address;
	uint32_t	controller_address;
	int			export_number;
	std::string pin_name;
} const PWM_BBB_ADDRINFO[PWM_MAX_PINS] =
{
	/* 1 */	{0x48302000, 0x48302200, 0, "P9.14"},  // EHRPWM1A, P9.14
	/* 2 */	{0x48302000, 0x48302200, 1, "P9.16"},  // EHRPWM1B, P9.16
	/* 3 */	{0x48304000, 0x48304200, 0, "P8.19"},  // EHRPWM2A, P8.19
	/* 4 */	{0x48304000, 0x48304200, 1, "P8.13"}   // EHRPWM2B, P8.13
};

PWM_beagleboneblack::PWM_beagleboneblack(int pin_number):
	PWM(pin_number),
	pwmchip_number(-1),
	exported(false),
	enabled(false),
	period_ns(0),
	duty_cycle_ns(0)
{
	search_pwmchip_number();
}

PWM_beagleboneblack::~PWM_beagleboneblack()
{
	disable_pwm();
	unexport_pwm();
}

bool PWM_beagleboneblack::enable(void)
{
	if (pwmchip_number < 0) return false;

	if (!config_pin())
		return false;

	if (!export_pwm())
		return false;

	if (!enable_pwm())
		return false;

	return true;
}

bool PWM_beagleboneblack::set_period_ns(unsigned int period)
{
	period_ns = period;

	std::ostringstream ostr;
	ostr << get_base_pwmx_folder() << "/period";

	std::ofstream duty_cycle_file;
	duty_cycle_file.open (ostr.str().c_str());
	duty_cycle_file << period_ns;
	duty_cycle_file.close();
	return true;
}

bool PWM_beagleboneblack::set_duty_cycle_ns(unsigned int duty)
{
	if (duty > period_ns)
	{
		std::cerr << "Duty cycle must be set to a value lower than period" << std::endl;
		return false;
	}

	duty_cycle_ns = duty;

	std::ostringstream ostr;
	ostr << get_base_pwmx_folder() << "/duty_cycle";

	std::ofstream duty_cycle_file;
	duty_cycle_file.open (ostr.str().c_str());
	duty_cycle_file << duty_cycle_ns;
	duty_cycle_file.close();
	return true;
}

bool PWM_beagleboneblack::search_pwmchip_number()
{
	bool rv = false;
	std::ostringstream ostr;
	ostr << "/sys/devices/platform/ocp/"
			<< std::hex << PWM_BBB_ADDRINFO[pin_number].chipset_address
			<< ".epwmss/"
			<< std::hex << PWM_BBB_ADDRINFO[pin_number].controller_address
			<< ".pwm/pwm";

	DIR* path = opendir(ostr.str().c_str());
	if (path != NULL)
	{
		dirent* entry;
		while ((entry = readdir(path)) != NULL && !rv)
		{
			std::string folder(entry->d_name);
			if (folder.find("pwmchip") != std::string::npos)
			{
				std::stringstream convert(folder.substr(7));
				if (! (convert >> pwmchip_number))
				{
					std::cerr << "pwmchip number for pin_number " << pin_number << " could not be read" << std::endl;
					continue;
				}
				else rv = true;
			}
		}
		if (!rv)
		{
			std::cerr << "pwmchip folder for pin_number " << pin_number << " can not be found" << std::endl;
		}
	}
	else
	{
		std::cerr << "pwm folder for pin_number " << pin_number << " can not be found" << std::endl;
	}

	closedir(path);
	return rv;
}

bool PWM_beagleboneblack::config_pin(bool set_to_default /* = false */)
{
	std::ostringstream cmd;
	cmd << "/usr/local/bin/config-pin " << PWM_BBB_ADDRINFO[pin_number].pin_name << (set_to_default? " default": " pwm");

	int rc = std::system(cmd.str().c_str());
	if (rc)
	{
		std::cerr << "Setting config pin for " << PWM_BBB_ADDRINFO[pin_number].pin_name << " to "  << (set_to_default? "default": "pwm") << " failed." << std::endl;
		return false;
	}
	return true;
}

bool PWM_beagleboneblack::export_pwm()
{
	std::ostringstream ostr;
	ostr << get_base_pwmchip_folder() << "/export";

	std::ofstream export_file;
	export_file.open (ostr.str().c_str());
	export_file << PWM_BBB_ADDRINFO[pin_number].export_number;
	export_file.close();

	exported = true;
	return true;
}

bool PWM_beagleboneblack::unexport_pwm()
{
	std::ostringstream ostr;
	ostr << get_base_pwmchip_folder() << "/unexport";

	std::ofstream export_file;
	export_file.open (ostr.str().c_str());
	export_file << PWM_BBB_ADDRINFO[pin_number].export_number;
	export_file.close();

	exported = false;
	return true;
}

bool PWM_beagleboneblack::enable_pwm()
{
	std::ostringstream ostr;
	ostr << get_base_pwmx_folder() << "/enable";

	std::ofstream export_file;
	export_file.open (ostr.str().c_str());
	export_file << "1";
	export_file.close();

	enabled = true;
	return true;
}

bool PWM_beagleboneblack::disable_pwm()
{
	std::ostringstream ostr;
	ostr << get_base_pwmx_folder() << "/enable";

	std::ofstream export_file;
	export_file.open (ostr.str().c_str());
	export_file << "1";
	export_file.close();

	enabled = false;
	return true;
}

std::string PWM_beagleboneblack::get_base_pwmchip_folder()
{
	if (pwmchip_number < 0)
	{
		std::cerr << "Cannot determine base pwmchip folder with pwmchip number = " << pwmchip_number << std::endl;
		return std::string();
	}

	std::ostringstream ostr;
	ostr << "/sys/class/pwm/pwmchip" << pwmchip_number;

	return ostr.str();
}

std::string PWM_beagleboneblack::get_base_pwmx_folder()
{
	if (!exported)
	{
		std::cerr << " Can not determine base pwmx folder when not exported" << std::endl;
		return std::string();
	}

	std::ostringstream ostr;
	ostr << get_base_pwmchip_folder() << "/pwm" << PWM_BBB_ADDRINFO[pin_number].export_number;

	return ostr.str();
}
