//============================================================================
// Name        : Beach Hunt
// Author      : Jon Whitmer, Justin Schaeffer, Ben Luzier, Gregory Williams
// Copyright   : 2022
// Description : program using inheritance that defines a parent object class, and four child classes: shell, wood, glass, and plant
//============================================================================

#include <iostream>
#include "item.h"
using namespace std;

#ifndef SHELL_H_
#define SHELL_H_

class Shell : public Item
{
	protected:
		double height;
	public:
		Shell(string color, double length, string description, double height); // constructor for Shell
		void setAll(string color, double length, string description, double height); // sets all of the values for Shell
		void setHeight(double height); // sets the height
		double getHeight(); // gets the height
		void print(); // prints the attributes of the class
};

#endif /* SHELL_H_ */
