//============================================================================
// Name        : Beach Hunt
// Author      : Jon Whitmer, Justin Schaeffer, Ben Luzier, Gregory Williams
// Copyright   : 2022
// Description : program using inheritance that defines a parent object class, and four child classes: shell, wood, glass, and plant
//============================================================================

#include <iostream>
#include "plant.h"
using namespace std;

Plant :: Plant(string color, double length, string description)
{
	this->color = color;
	this->length = length;
	this->description = description;
}

void Plant :: print()
{
	if (islower(this->color[0]))
	{
		this->color[0] = toupper(this->color[0]);
	}
	if (islower(this->description[0]))
	{
		this->description[0] = toupper(this->description[0]);
	}

	cout << "Color: " << color << " | ";
	cout << "Length: " << length << " inches" << " | ";
	cout << "Description: " << description << endl;
	cout << endl;
}




