/*
 * joystick.h
 *
 *  Created on: Aug 20, 2016
 *      Author:
 */

#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <iostream>
#include <fcntl.h>
#include <math.h>
#include <linux/joystick.h>
#include <vector>
#include <unistd.h>

// A new joystick is typicaly set as js2 in the current debian, so for now we keep this as default
// TODO: make this a setting in the project
#define JOYSTICK_DEV "/dev/input/js2"

struct joystick_position {
	float theta, r, x, y;
};

struct joystick_state {
	std::vector<signed short> button;
	std::vector<signed short> axis;
};

class cJoystick {
  private:
	pthread_t thread;
	bool active;
	int joystick_fd;
	js_event *joystick_ev;
	joystick_state *joystick_st;
	__u32 version;
	__u8 axes;
	__u8 buttons;
	char name[256];

  protected:
  public:
	cJoystick();
	~cJoystick();
	static void* loop(void* obj);
	void readEv();
	joystick_position joystickPosition(int n);
        bool buttonPressed(int n);
};

#endif
