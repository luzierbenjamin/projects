//============================================================================
// Name        : Beach Hunt
// Author      : Jon Whitmer, Justin Schaeffer, Ben Luzier, Gregory Williams
// Copyright   : 2022
// Description : program using inheritance that defines a parent object class, and four child classes: shell, wood, glass, and plant
//============================================================================

#include <iostream>
#include "glass.h"
using namespace std;

Glass :: Glass(string color, double length, string description, string origin)
{
	this->color = color;
	this->length = length;
	this->description = description;
	this->origin = origin;
}

void Glass :: setAll(string color, double length, string description, string origin)
{
	setColor(color);
	setLength(length);
	setDescription(description);
	setOrigin(origin);
}

void Glass :: setOrigin(string origin)
{
	this->origin = origin;
}

string Glass :: getOrigin()
{
	return origin;
}

void Glass :: print()
{
	if (islower(this->color[0]))
	{
		this->color[0] = toupper(this->color[0]);
	}
	if (islower(this->description[0]))
	{
		this->description[0] = toupper(this->description[0]);
	}
	if (islower(this->origin[0]))
	{
		this->origin[0] = toupper(this->origin[0]);
	}

	cout << "Color: " << color << " | ";
	cout << "Length: " << length << " inches" << " | ";
	cout << "Description: " << description << " | ";
	cout << "Origin: " << origin << endl;
	cout << endl;
}



