//============================================================================
// Name        : Beach Hunt
// Author      : Jon Whitmer, Justin Schaeffer, Ben Luzier, Gregory Williams
// Copyright   : 2022
// Description : program using inheritance that defines a parent object class, and four child classes: shell, wood, glass, and plant
//============================================================================

#include <iostream>
#include "shell.h"
using namespace std;

Shell :: Shell(string color, double length, string description, double height)
{
	this->color = color;
	this->length = length;
	this->description = description;
	this->height = height;
}

void Shell :: setAll(string color, double length, string description, double height)
{
	setColor(color);
	setLength(length);
	setDescription(description);
	setHeight(height);
}

void Shell :: setHeight(double height)
{
	this->height = height;
}

double Shell :: getHeight()
{
	return height;
}

void Shell :: print()
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
	cout << "Description: " << description << " | ";
	cout << "Height: " << height << " inches" << endl;
	cout << endl;
}




