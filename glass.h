//============================================================================
// Name        : Beach Hunt
// Author      : Jon Whitmer, Justin Schaeffer, Ben Luzier, Gregory Williams
// Copyright   : 2022
// Description : program using inheritance that defines a parent object class, and four child classes: shell, wood, glass, and plant
//============================================================================

#include <iostream>
#include "item.h"
using namespace std;

#ifndef GLASS_H_
#define GLASS_H_

class Glass : public Item
{
	protected:
		string origin;
	public:
		Glass(string color, double length, string description, string origin); // constructor for the Glass class
		void setAll(string color, double length, string description, string origin); // sets all the possible values for Glass
		void setOrigin(string origin); // sets the origin
		string getOrigin(); // gets the origin
		void print(); // // prints the attributes of the class
};

#endif /* GLASS_H_ */
