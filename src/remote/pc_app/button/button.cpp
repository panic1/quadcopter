/*
 * joystick.cpp
 *
 *  Created on: Aug 20, 2016
 *      Author: Kris Stremerch
 */

#include "button.h"

Button::Button(int number, std::string name) {
	this->number = number;
	this->name = name;
	this->pressed = false;
}


Button::~Button() {
}

void Button::press()
{

}

void Button::isPressed()
{

}
