//============================================================================
// Name        : Beach Hunt
// Author      : Jon Whitmer, Justin Schaeffer, Ben Luzier, Gregory Williams
// Copyright   : 2022
// Description : program using inheritance that defines a parent object class, and four child classes: shell, wood, glass, and plant
//============================================================================

#include <iostream>
#include "item.h"
using namespace std;

#ifndef WOOD_H_
#define WOOD_H_

class Wood : public Item
{
	protected:
		string brightness;
	public:
		Wood(string color, double length, string description, string brightness); // constructor for Wood
		void setAll(string color, double length, string description, string brightness); // sets all the values possible for Wood
		void setBrightness(string brightness); // sets the brightness
		string getBrightness(); // gets the brightness
		void print(); // prints the attributes of the class
};

#endif /* WOOD_H_ */
