/*
 * i2c.cpp
 *
 *  Created on: 18-aug.-2016
 *      Author: nicky
 */

#include <cstring>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include "i2c.hpp"

I2C::I2C(unsigned int bus_number, uint8_t slave_address):
	fd(-1),
	slave_address(slave_address)
{
	std::ostringstream ostr;
	ostr << "/dev/i2c-" << bus_number;
	path = ostr.str();

	std::cout << "I2C port path: " <<  path << std::endl;
}

I2C::~I2C()
{
	if (fd != -1)
		close();
}

bool I2C::open(uint fdflags)
{
	fd = ::open(path.c_str(), fdflags);
	if (fd == -1)
	{
		std::cerr << "Could not open i2c file descriptor." << std::endl;
	}
	else
		return true;
	return false;
}

bool I2C::close()
{
	if (!::close(fd))
	{
		fd = -1;
		return true;
	}
	else
		std::cerr << "Could not close i2c file descriptor." << std::endl;
	return false;
}

bool I2C::write_byte(uint8_t register_address, uint8_t value)
{
	set_slave_address();

	i2c_smbus_data data;
    data.byte = value;

    return use_smbus_IOCTL(true, register_address, I2C_SMBUS_BYTE_DATA, data);
}

bool I2C::write_word(uint8_t register_address, uint16_t value)
{
	set_slave_address();

	i2c_smbus_data data;
	data.word = value;

	return use_smbus_IOCTL(true, register_address, I2C_SMBUS_WORD_DATA, data);
}

uint8_t I2C::write_block(uint8_t register_address, uint8_t* value, size_t length)
{
	set_slave_address();

	if( length > I2C_SMBUS_BLOCK_MAX )
    {
        length = I2C_SMBUS_BLOCK_MAX;
    }

    i2c_smbus_data data;

    memset(data.block, 0, length+1);
    memcpy( &(data.block[1]), value, length);
    data.block[0] = length;

    if (use_smbus_IOCTL(true, register_address, I2C_SMBUS_I2C_BLOCK_DATA, data))
    {
    	return length;
    }
    else
    {
    	return 0;
    }
}

bool I2C::read_byte(uint8_t register_address, uint8_t& value)
{
    set_slave_address();

    i2c_smbus_data data;
    if( use_smbus_IOCTL(false, register_address, I2C_SMBUS_BYTE_DATA, data) != 0)
	{
		value = data.byte;
		return true;
	}
	else
	{
		return false;
	}
}

bool I2C::read_word(uint8_t register_address, uint16_t& value)
{
    set_slave_address();

    i2c_smbus_data data;
    if( use_smbus_IOCTL(false, register_address, I2C_SMBUS_WORD_DATA, data) != 0)
	{
		value = data.word;
		return true;
	}
	else
	{
		return false;
	}
}

uint8_t I2C::read_block(uint8_t register_address, uint8_t* value, size_t length)
{
    set_slave_address();
    if( length > I2C_SMBUS_BLOCK_MAX )
    {
        length = I2C_SMBUS_BLOCK_MAX;
    }

    i2c_smbus_data data;
    data.block[0] = length;

    if( use_smbus_IOCTL(false, register_address, I2C_SMBUS_I2C_BLOCK_DATA, data) )
    {
        memcpy(value, &(data.block[1]), length);
        return data.block[0];
    }
    else
    {
        return 0;
    }
}

bool I2C::set_slave_address()
{
	return ::ioctl(fd, I2C_SLAVE, slave_address) >= 0;
}

inline bool I2C::use_smbus_IOCTL(bool write_mode, uint8_t register_address, size_t size, i2c_smbus_data &data)
{
	i2c_smbus_ioctl_data smbusPackage;

	smbusPackage.read_write = write_mode? I2C_SMBUS_WRITE : I2C_SMBUS_READ;
	smbusPackage.command    = register_address;
	smbusPackage.size       = size;
	smbusPackage.data       = &data;

	return ::ioctl(fd, I2C_SMBUS, &smbusPackage) >= 0;
}
