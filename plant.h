//============================================================================
// Name        : Beach Hunt
// Author      : Jon Whitmer, Justin Schaeffer, Ben Luzier, Gregory Williams
// Copyright   : 2022
// Description : program using inheritance that defines a parent object class, and four child classes: shell, wood, glass, and plant
//============================================================================

#include <iostream>
#include "item.h"
using namespace std;

#ifndef PLANT_H_
#define PLANT_H_

class Plant : public Item
{
	public:
		Plant(string color, double length, string description); // constructor for Plant
		void print(); // prints the attributes of the class
};

#endif /* PLANT_H_ */
