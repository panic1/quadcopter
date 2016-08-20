/*
 * main.cpp
 *
 *  Created on: Nov 28, 2014
 *      Author: Nicky Geerts
 *  Last changed on: Aug 20 2016
 *              by : Kris Stremerch
 */

#include <iostream>
#include <iomanip>
#include "src/joystick.h"
using namespace std;

int main(void) {
	cJoystick js; joystick_position jp[2];
	joystick_position jp_old[2];

	bool active = true;

	while(active) {

		jp[0] = js.joystickPosition(0);
		jp[1] = js.joystickPosition(1);
		//if( jp_old[0].x != jp[0].x || jp_old[0].y != jp[0].y )
		if( (roundf(jp_old[0].x * 10) / 10  != roundf(jp[0].x * 10) / 10 ) || (roundf(jp_old[0].y * 10) / 10  != roundf(jp[0].y * 10) / 10 ) || (roundf(jp_old[1].x * 10) / 10  != roundf(jp[1].x * 10) / 10 ) || (roundf(jp_old[1].y * 10) / 10  != roundf(jp[1].y * 10) / 10 ) )
		{
			cout << "Left stick X value: " << setw(10)<< jp[0].x << " Y value: " << setw(10)<< jp[0].y << " theta value: "<< setw(10)<< jp[0].theta << " r: "  << setw(10)<< jp[0].r  << "    Right stick X value: " << setw(10)<< jp[1].x << " Y value: " << setw(10)<< jp[1].y << " theta value: "<< setw(10)<< jp[1].theta << " r: "  << setw(10)<< jp[1].r << std::endl;
			//cout << "rounded jp_old[0].x: " << roundf(jp_old[0].x * 10) / 10 << " rounded jp_old[0].y: " << (roundf(jp_old[0].y * 10) / 10) << " rounded jp_old[1].x: " << roundf(jp_old[1].x * 10) / 10 << " rounded jp_old[1].y: " << (roundf(jp_old[1].y * 10) / 10)  << std::endl; //for debug only
		}

		jp_old[0] = js.joystickPosition(0);
		jp_old[1] = js.joystickPosition(1);
	}

	return 0;
}

