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

#include "joystick/joystick.h"
using namespace std;

int main(void) {
	cJoystick js; joystick_position jp[8];
	joystick_position jp_old[8];

	bool active = true;	 //XBox360 buttons 			PS3 buttons
	bool button0_pressed; //A
	bool button1_pressed; //B
	bool button2_pressed; //X
	bool button3_pressed; //Y
	bool button4_pressed; //LB
	bool button5_pressed; //RB
	bool button6_pressed; //Back
	bool button7_pressed; //Start
	bool button8_pressed; //XBox
	bool button9_pressed; //Left thumb stick press
	bool button10_pressed; // Right thumb stick press

	/* 	XBox360 controller:
		left thumbstick X: axis 0.x
		left thumbstick Y: axis 0.y
		right thumbstick X: axis 1.y (inverse)
		right thumbstick X: axis 2.x (inverse)
		Left Trigger  (LT): axis 1.x
		Right Trigger (RT): axis 2.y (inverse)
		+ horixontal	  : axis 3.x
		+ vertical		  : axis3.y
	*/

	while(active) {

		jp[0] = js.joystickPosition(0);
		jp[1] = js.joystickPosition(1);
		jp[2] = js.joystickPosition(2);
		jp[3] = js.joystickPosition(3);
		jp[4] = js.joystickPosition(4);
		jp[5] = js.joystickPosition(5);
		jp[6] = js.joystickPosition(6);
		jp[7] = js.joystickPosition(7);

		if( js.buttonPressed(0) != 0 && !button0_pressed )
		{
			button0_pressed = true;
			cout << "Button 0 pressed" << std::endl;
		}
		else
		{
			button0_pressed = false;
		}

		if( js.buttonPressed(1) != 0 && !button1_pressed )
		{
			button1_pressed = true;
			cout << "Button 1 pressed" << std::endl;
		}
		else
		{
			button1_pressed = false;
		}

		if( js.buttonPressed(2) != 0 && !button2_pressed )
		{
			button2_pressed = true;
			cout << "Button 2 pressed" << std::endl;
		}
		else
		{
			button2_pressed = false;
		}

		if( js.buttonPressed(3) != 0 && !button3_pressed )
		{
			button3_pressed = true;
			cout << "Button 3 pressed" << std::endl;
		}
		else
		{
			button3_pressed = false;
		}

		if( js.buttonPressed(4) != 0 && !button4_pressed )
		{
			button4_pressed = true;
			cout << "Button 4 pressed" << std::endl;
		}
		else
		{
			button4_pressed = false;
		}

		if( js.buttonPressed(5) != 0 && !button5_pressed )
		{
			button5_pressed = true;
			cout << "Button 5 pressed" << std::endl;
		}
		else
		{
			button5_pressed = false;
		}

		if( js.buttonPressed(6) != 0 && !button6_pressed )
		{
			button6_pressed = true;
			cout << "Button 6 pressed" << std::endl;
		}
		else
		{
			button6_pressed = false;
		}

		if( js.buttonPressed(7) != 0 && !button7_pressed )
		{
			button7_pressed = true;
			cout << "Button 7 pressed" << std::endl;
		}
		else
		{
			button7_pressed = false;
		}

		if( js.buttonPressed(8) != 0 && !button8_pressed )
		{
			button8_pressed = true;
			cout << "Button 8 pressed" << std::endl;
		}
		else
		{
			button8_pressed = false;
		}

		if( js.buttonPressed(9) != 0 && !button9_pressed )
		{
			button9_pressed = true;
			cout << "Button 9 pressed" << std::endl;
		}
		else
		{
			button9_pressed = false;
		}

		if( js.buttonPressed(10) != 0 && !button10_pressed )
		{
			button10_pressed = true;
			cout << "Button 10 pressed" << std::endl;
		}
		else
		{
			button10_pressed = false;
		}



		if( (roundf(jp_old[0].x * 10) / 10  != roundf(jp[0].x * 10) / 10 ) || (roundf(jp_old[0].y * 10) / 10  != roundf(jp[0].y * 10) / 10 ) || (roundf(jp_old[1].x * 10) / 10  != roundf(jp[1].x * 10) / 10 ) || (roundf(jp_old[1].y * 10) / 10  != roundf(jp[1].y * 10) / 10 )
				|| (roundf(jp_old[2].x * 10) / 10  != roundf(jp[2].x * 10) / 10 ) || (roundf(jp_old[2].y * 10) / 10  != roundf(jp[2].y * 10) / 10 )
				|| (roundf(jp_old[3].x * 10) / 10  != roundf(jp[3].x * 10) / 10 ) || (roundf(jp_old[3].y * 10) / 10  != roundf(jp[3].y * 10) / 10 )
				|| (roundf(jp_old[4].x * 10) / 10  != roundf(jp[4].x * 10) / 10 ) || (roundf(jp_old[4].y * 10) / 10  != roundf(jp[4].y * 10) / 10 )
				|| (roundf(jp_old[5].x * 10) / 10  != roundf(jp[5].x * 10) / 10 ) || (roundf(jp_old[5].y * 10) / 10  != roundf(jp[5].y * 10) / 10 )
				|| (roundf(jp_old[6].x * 10) / 10  != roundf(jp[6].x * 10) / 10 ) || (roundf(jp_old[6].y * 10) / 10  != roundf(jp[6].y * 10) / 10 )
				|| (roundf(jp_old[7].x * 10) / 10  != roundf(jp[7].x * 10) / 10 ) || (roundf(jp_old[7].y * 10) / 10  != roundf(jp[7].y * 10) / 10 )
				)
		{
			//cout << "Left stick X value: " << setw(10)<< jp[0].x << " Y value: " << setw(10)<< jp[0].y << " theta value: "<< setw(10)<< jp[0].theta << " r: "  << setw(10)<< jp[0].r  << "Right stick X value:      " << setw(10)<< jp[1].x << " Y value: " << setw(10)<< jp[1].y << " theta value: "<< setw(10)<< jp[1].theta << " r: "  << setw(10)<< jp[1].r << std::endl;
			cout << "axis 0 X value:  " << setw(10)<< jp[0].x << " Y value: " << setw(10)<< jp[0].y << "    axis 1 X value:  " << setw(10)<< jp[1].x << " Y value: " << setw(10)<< jp[1].y << std::endl;
			cout << "axis 2 X value:  " << setw(10)<< jp[2].x << " Y value: " << setw(10)<< jp[2].y << "    axis 3 X value:  " << setw(10)<< jp[3].x << " Y value: " << setw(10)<< jp[3].y << std::endl;
			cout << "axis 4 X value:  " << setw(10)<< jp[4].x << " Y value: " << setw(10)<< jp[4].y << "    axis 5 X value:  " << setw(10)<< jp[5].x << " Y value: " << setw(10)<< jp[5].y << std::endl;
			cout << "axis 6 X value:  " << setw(10)<< jp[6].x << " Y value: " << setw(10)<< jp[6].y << "    axis 7 X value:  " << setw(10)<< jp[7].x << " Y value: " << setw(10)<< jp[7].y << std::endl;
			//cout << "rounded jp_old[0].x: " << roundf(jp_old[0].x * 10) / 10 << " rounded jp_old[0].y: " << (roundf(jp_old[0].y * 10) / 10) << " rounded jp_old[1].x: " << roundf(jp_old[1].x * 10) / 10 << " rounded jp_old[1].y: " << (roundf(jp_old[1].y * 10) / 10)  << std::endl; //for debug only
		}

		jp_old[0] = js.joystickPosition(0);
		jp_old[1] = js.joystickPosition(1);
		jp_old[2] = js.joystickPosition(2);
		jp_old[3] = js.joystickPosition(3);
		jp_old[4] = js.joystickPosition(4);
		jp_old[5] = js.joystickPosition(5);
		jp_old[6] = js.joystickPosition(6);
		jp_old[7] = js.joystickPosition(7);
	}

	return 0;
}

