/*
 * button.h
 *
 *  Created on: Aug 20, 2016
 *      Author: Kris Stremerch
 */

#include <string>
using namespace std;

class Button {
  private:
	int number;
	std::string name;
	bool pressed;

  protected:
  public:
	Button(int number, std::string name);
	~Button();

    void press();
    void isPressed();
};
