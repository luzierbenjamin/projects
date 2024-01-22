//============================================================================
// Name        : Beach Hunt
// Author      : Jon Whitmer, Justin Schaeffer, Ben Luzier, Gregory Williams
// Copyright   : 2022
// Description : program using inheritance that defines a parent object class, and four child classes: shell, wood, glass, and plant
//============================================================================

#include <iostream>
#include "wood.h"
using namespace std;

Wood :: Wood(string color, double length, string description, string brightness)
{
	this->color = color;
	this->length = length;
	this->description = description;
	this->brightness = brightness;
}

void Wood :: setAll(string color, double length, string description, string brightness)
{
	setColor(color);
	setLength(length);
	setDescription(description);
	setBrightness(brightness);
}

void Wood :: setBrightness(string brightness)
{
	this->brightness = brightness;
}

string Wood :: getBrightness()
{
	return brightness;
}

void Wood :: print()
{
	if (islower(this->color[0]))
	{
		this->color[0] = toupper(this->color[0]);
	}
	if (islower(this->description[0]))
	{
		this->description[0] = toupper(this->description[0]);
	}
	if (islower(this->brightness[0]))
	{
		this->brightness[0] = toupper(this->brightness[0]);
	}

	cout << "Color: " << color << " | ";
	cout << "Length: " << length << " inches" << " | ";
	cout << "Description: " << description << " | ";
	cout << "Brightness: " << brightness << endl;
	cout << endl;
}




