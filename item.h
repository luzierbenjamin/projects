//============================================================================
// Name        : Beach Hunt
// Author      : Jon Whitmer, Justin Schaeffer, Ben Luzier, Gregory Williams
// Copyright   : 2022
// Description : program using inheritance that defines a parent object class, and four child classes: shell, wood, glass, and plant
//============================================================================

#include <iostream>
using namespace std;

#ifndef ITEM_H_
#define ITEM_H_

class Item
{
	protected:
		string color;
		double length;
		string description;
	public:
		Item(); // constructor with 0 values for parent class Item
		Item(string color, double length, string description); // constructor for parent class Item
		void setAll(string color, double length, string description); // sets all of the possible attributes
		void setColor(string color); // sets the color
		string getColor(); // gets the color
		void setLength(double length); // sets the length in inches
		double getLength(); // gets the length in inches
		void setDescription(string description); // sets the description attribute
		string getDescription(); // gets the description attribute
		void print(); // prints the attributes of the class
};

#endif /* ITEM_H_ */
