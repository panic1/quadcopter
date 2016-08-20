/*
 * i2c.hpp
 *
 *  Created on: 18-aug.-2016
 *      Author: nicky
 */

#ifndef HAL_I2C_I2C_HPP_
#define HAL_I2C_I2C_HPP_

#include <stdint.h>
#include <string>
#include <fcntl.h>
#include <linux/i2c.h>

class I2C
{
public:
	I2C(unsigned int bus_number, uint8_t slave_address);
	~I2C();

	bool open(uint fdflags);
	bool close();

	bool write_byte(uint8_t register_address, uint8_t value);
	bool write_word(uint8_t register_address, uint16_t value);
	uint8_t write_block(uint8_t register_address, uint8_t* value, size_t length);
	bool read_byte(uint8_t register_address, uint8_t& value);
	bool read_word(uint8_t register_address, uint16_t& value);
	uint8_t read_block(uint8_t register_address, uint8_t* value, size_t length);

private:
	bool set_slave_address();
    inline bool use_smbus_IOCTL(bool write_mode, uint8_t register_address, size_t size, i2c_smbus_data &data);


	int 		fd;
	std::string path;
	uint8_t 	slave_address;

};

#endif /* HAL_I2C_I2C_HPP_ */
