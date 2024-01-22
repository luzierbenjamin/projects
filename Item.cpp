//============================================================================
// Name        : Beach Hunt
// Author      : Jon Whitmer, Justin Schaeffer, Ben Luzier, Gregory Williams
// Copyright   : 2022
// Description : program using inheritance that defines a parent object class, and four child classes: shell, wood, glass, and plant
//============================================================================

#include <iostream>
#include "item.h"
using namespace std;

Item :: Item()
{
	this->color = "N/A";
	this->length = 0.0;
	this->description = "N/A";
}

Item :: Item(string color, double length, string description)
{
	this->color = color;
	this->length = length;
	this->description = description;
}

void Item :: setAll(string color, double length, string description)
{
	setColor(color);
	setLength(length);
	setDescription(description);
}

void Item :: setColor(string color)
{
	this->color = color;
}

string Item :: getColor()
{
	return color;
}

void Item :: setLength(double length)
{
	this->length = length;
}

double Item :: getLength()
{
	return length;
}

void Item :: setDescription(string description)
{
	this->description= description;
}

string Item :: getDescription()
{
	return description;
}

void Item :: print()
{
	cout << "Color: " << color << endl;
	cout << "Length: " << length << " inches" << endl;
	cout << "Description: " << description << endl;
	cout << endl;
}
