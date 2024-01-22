//============================================================================
// Name        : Beach Hunt
// Author      : Jon Whitmer, Justin Schaeffer, Ben Luzier, Gregory Williams
// Copyright   : 2022
// Description : program using inheritance that defines a parent object class, and four child classes: shell, wood, glass, and plant
//============================================================================

#include <iostream>
#include <vector>
#include <string>
#include "item.h"
#include "glass.h"
#include "shell.h"
#include "wood.h"
#include "plant.h"
using namespace std;

void ShellSetter(Shell & Shell1, Shell & Shell2, Shell & Shell3, Shell & Shell4, Shell & Shell5, vector<Shell> & shells); // sets the Shell vector
void PlantSetter(Plant & Plant1, Plant & Plant2, Plant & Plant3, Plant & Plant4, Plant & Plant5, Plant & Plant6, vector<Plant> & plants); // sets the Plant vector
void GlassSetter(Glass & Glass1, Glass & Glass2, vector<Glass> & glass); // sets the Glass Vector
void WoodSetter(Wood & Wood1, Wood & Wood2, Wood & Wood3, vector<Wood> & wood); // sets the Wood Vector
void inputItems(vector<Shell> & shells, vector<Wood> & wood, vector<Plant> & plants, vector<Glass> & glass); // allows user to input items into vector of their choosing
void searchItems(vector<Shell> & shells, vector<Wood> & wood, vector<Plant> & plants, vector<Glass> & glass); // allows user to search all of the vectors for specific attributes
void finalInventory(vector<Shell> & shells, vector<Wood> & wood, vector<Plant> & plants, vector<Glass> & glass); // displays the final collection data

int main() {
	// Initialization of Items
	vector<Glass> glass;
	vector<Shell> shells;
	vector<Wood> wood;
	vector<Plant> plants;
	Plant Plant1("green", 10, "solid"), Plant2("brown", 6, "grass-like"), Plant3("black", 12, "wiggly"), Plant4("tan", 8.5, "solid"), Plant5("green", 10, "solid"), Plant6("green", 10, "solid");
	Wood Wood1("brown", 6, "plain", "light"), Wood2("brown", 2, "plain", "medium"), Wood3("brown", 4.5, "variagated", "dark");
	Shell Shell1("white", 3, "concave", 0.5), Shell2("pink", 2, "circular", 0.25), Shell3("orange", 0.5, "flat", 0.25), Shell4("brown", 1, "convex", 0.25), Shell5("white", 3, "concave", 1.5);
	Glass Glass1("clear", 1, "shiny", "man made"), Glass2("white", 2.5, "scratched", "unknown origin");
	int status = 0;

	ShellSetter(Shell1, Shell2, Shell3, Shell4, Shell5, shells);
	WoodSetter(Wood1,Wood2,Wood3, wood);
	PlantSetter(Plant1,Plant2,Plant3,Plant4,Plant5,Plant6, plants);
	GlassSetter(Glass1, Glass2, glass);
	do
	{
		status = 0;
		cout << "Welcome to Beach Hunt!  Pick what you wish to do: " << endl;
		cout << "1] Collect Items" << endl;
		cout << "2] Search Items" << endl;
		cout << "3] End Program" << endl;
		cin >> status;
		switch(status)
		{
			case 1:
				inputItems(shells, wood, plants, glass);
				break;
			case 2:
				searchItems(shells, wood, plants, glass);
				break;
			case 3:
				break;
			default:
				cout << "Invalid Option.  Try Again." << endl;
		}
	} while (status != 3);
	finalInventory(shells, wood, plants, glass);
	return 0;
}

void ShellSetter(Shell & Shell1, Shell & Shell2, Shell & Shell3, Shell & Shell4, Shell & Shell5, vector<Shell> & shells)
{
	shells.push_back(Shell1);
	shells.push_back(Shell2);
	shells.push_back(Shell3);
	shells.push_back(Shell4);
	shells.push_back(Shell5);
}

void WoodSetter(Wood & Wood1, Wood & Wood2, Wood & Wood3, vector<Wood> & wood)
{
	wood.push_back(Wood1);
	wood.push_back(Wood2);
	wood.push_back(Wood3);
}

void PlantSetter(Plant & Plant1, Plant & Plant2, Plant & Plant3, Plant & Plant4, Plant & Plant5, Plant & Plant6, vector<Plant> & plants)
{
	plants.push_back(Plant1);
	plants.push_back(Plant2);
	plants.push_back(Plant3);
	plants.push_back(Plant4);
	plants.push_back(Plant5);
	plants.push_back(Plant6);
}

void GlassSetter(Glass & Glass1, Glass & Glass2, vector<Glass> & glass)
{
	glass.push_back(Glass1);
	glass.push_back(Glass2);
}

void inputItems(vector<Shell> & shells, vector<Wood> & wood, vector<Plant> & plants, vector<Glass> & glass)
{
	int option;
	string input1, input2, input3, input4;
	Shell tempShell("N/A", 0.0, "N/A", 0.0);
	Wood tempWood("N/A", 0.0, "N/A", "N/A");
	Plant tempPlant("N/A", 0.0, "N/A");
	Glass tempGlass("N/A", 0.0, "N/A", "N/A");
	do
	{
		option = 0;
		cout << "Enter your item you found on the beach: " << endl;
		cout << "1] Shell"<< endl;
		cout << "2] Wood" << endl;
		cout << "3] Glass" << endl;
		cout << "4] Plant" << endl;
		cout << "5] Stop Collecting" << endl;
		cin >> option;
		switch(option)
		{
			case 1:
				cout << "Enter the characteristics of your shell" << endl;
				cout << "Color: ";
				cin >> input1;
				cout << "Length: ";
				cin >> input2;
				cout << "Description: ";
				cin >> input3;
				cout << "Height: ";
				cin >> input4;
				tempShell.setAll(input1, (stod(input2)), input3, (stod(input4)));
				shells.push_back(tempShell);
				break;
			case 2:
				cout << "Enter the characteristics of your wood" << endl;
				cout << "Color: ";
				cin >> input1;
				cout << "Length: ";
				cin >> input2;
				cout << "Description: ";
				cin >> input3;
				cout << "Brightness: ";
				cin >> input4;
				tempWood.setAll(input1, (stod(input2)), input3, input4);
				wood.push_back(tempWood);
				break;
			case 3:
				cout << "Enter the characteristics of your glass" << endl;
				cout << "Color: ";
				cin >> input1;
				cout << "Length: ";
				cin >> input2;
				cout << "Description: ";
				cin >> input3;
				cout << "Origin: ";
				cin >> input4;
				tempGlass.setAll(input1, (stod(input2)), input3, input4);
				glass.push_back(tempGlass);
				break;
			case 4:
				cout << "Enter the characteristics of your plant" << endl;
				cout << "Color: ";
				cin >> input1;
				cout << "Length: ";
				cin >> input2;
				cout << "Description: ";
				cin >> input3;
				tempPlant.setAll(input1, (stod(input2)), input3);
				plants.push_back(tempPlant);
				break;
			case 5:
				cout << "Returning to Menu..." << endl << endl;
				break;
			default:
				cout << "Invalid Input" << endl;
				break;
		}
	} while(option != 5);
}

void searchItems(vector<Shell> & shells, vector<Wood> & wood, vector<Plant> & plants, vector<Glass> & glass)
{
	vector<int> possible_values((shells.size() + wood.size() + plants.size() + glass.size()), 0);
	string color_search;
	double minimum, maximum;
	int size = shells.size(), max_size, i;
	int total_values = 0, categorical_values[4] = {0};

	cout << "You are now searching" << endl;
	cout << "Enter color: ";
	cin >> color_search;
	cout << "Enter minimum length (in inches): ";
	cin >> minimum;
	cout << "Enter maximum length (in inches): ";
	cin >> maximum;
	cout << endl;
	cout << "<<<< SEARCH RESULTS >>>>" << endl << endl;;

	// Shell Search
	for (i = 0; i < size; i++)
	{
		if (shells[i].getColor().compare(color_search) == 0)
		{
			possible_values[i]++;
		}
		if ((shells[i].getLength() >= minimum) && (shells[i].getLength() <= maximum))
		{
			possible_values[i]++;
		}
	}
	size = possible_values.size();
	cout << "<<SHELLS>>" << endl;
	for (i = 0; i < size; i++)
	{
		if (possible_values[i] == 2)
		{
			cout << "[Shell #" << (i + 1) << "] -- ";
			shells[i].print();
			total_values++;
			categorical_values[0]++;
		}
	}
	if (categorical_values[0] == 0)
	{
		cout << "None" << endl << endl;
	}
	size = shells.size();
	max_size = wood.size();

	// Wood Search
	for (i = size; i < max_size + size; i++)
	{
		if (wood[i - size].getColor().compare(color_search) == 0)
		{
			possible_values[i]++;
		}
		if ((shells[i - size].getLength() >= minimum) && (shells[i - size].getLength() <= maximum))
		{
			possible_values[i]++;
		}
	}
	cout << "<<WOOD>>" << endl;
	for (i = size; i < max_size + size; i++)
	{
		if (possible_values[i] == 2)
		{
			cout << "[Wood #" << ((i - size) + 1) << "] -- ";
			wood[i - size].print();
			total_values++;
			categorical_values[1]++;
		}
	}
	if (categorical_values[1] == 0)
	{
		cout << "None" << endl << endl;
	}
	size = shells.size() + wood.size();
	max_size = plants.size();

	// Plant Search
	for (i = size; i < max_size + size; i++)
	{
		if (plants[i - size].getColor().compare(color_search) == 0)
		{
			possible_values[i]++;
		}
		if ((plants[i - size].getLength() >= minimum) && (plants[i - size].getLength() <= maximum))
		{
			possible_values[i]++;
		}
	}
	cout << "<<PLANTS>>" << endl;
	for (i = size; i < max_size + size; i++)
	{
		if (possible_values[i] == 2)
		{
			cout << "[Plant #" << ((i - size) + 1) << "] -- ";
			plants[i - size].print();
			total_values++;
			categorical_values[2]++;
		}
	}
	if (categorical_values[2] == 0)
	{
		cout << "None" << endl << endl;
	}
	size = shells.size() + wood.size() + plants.size();
	max_size = glass.size();

	// Glass Search
	for (i = size; i < max_size + size; i++)
	{
		if (glass[i - size].getColor().compare(color_search) == 0)
		{
			possible_values[i]++;
		}
		if ((glass[i - size].getLength() >= minimum) && (glass[i - size].getLength() <= maximum))
		{
			possible_values[i]++;
		}
	}
	cout << "<<GLASS>>" << endl;
	for (i = size; i < max_size + size; i++)
	{
		if (possible_values[i] == 2)
		{
			cout << "[Glass #" << ((i - size) + 1) << "] -- ";
			glass[i - size].print();
			total_values++;
			categorical_values[3]++;
		}
	}
	if (categorical_values[3] == 0)
	{
		cout << "None" << endl << endl;
	}

	if (total_values == 0)
	{
		cout << endl << endl;
		cout << "There were no items found matching the search request" << endl << endl;
	}
	else
	{
		cout << endl;
	}
}

void finalInventory(vector<Shell> & shells, vector<Wood> & wood, vector<Plant> & plants, vector<Glass> & glass)
{
	int i, size;

	cout << "Program has ended!  Here is your collection:" << endl << endl;

	size = shells.size();
	cout << "<<SHELLS>>" << endl;
	for (i = 0; i < size; i++)
	{
		cout << "[Shell #" << i + 1 << "] -- ";
		shells[i].print();
	}

	size = wood.size();
	cout << "<<WOOD>>" << endl;
	for (i = 0; i < size; i++)
	{
		cout << "[Wood #" << i + 1 << "] -- ";
		wood[i].print();
	}

	size = plants.size();
	cout << "<<PLANTS>>" << endl;
	for (i = 0; i < size; i++)
	{
		cout << "[Plant #" << i + 1 << "] -- ";
		plants[i].print();
	}

	size = glass.size();
	cout << "<<GLASS>>" << endl;
	for (i = 0; i < size; i++)
	{
		cout << "[Glass #" << i + 1 << "] -- ";
		glass[i].print();
	}
}
