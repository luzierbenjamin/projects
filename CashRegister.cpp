//============================================================================
// Name        : CPSC246 Cash Register Object Project
// Author      : Jon Whitmer, Justin Schaeffer, Benjamin Luzier
// Copyright   : 2022
// Description : to develop a "cash register" class and implementation to simulate the use of a cash ONLY register
//============================================================================

#include <iostream>
#include <vector>
#include <fstream>
#include <cctype>
#include <string>
#include <string.h>
#include <iomanip>
using namespace std;

class Item {
	public:
		Item(); // constructor if no values are set
		Item(int onHand, double cost, string name); // constructor that assigns the primary three attributes to Item
		void setName(string name); // sets the name
		string getName(); // gets the name
		void setCost(double cost); // sets the denomination value
		double getCost(); // gets the denomination value
		void setonHand(int onHand); // sets the quantity
		int getonHand(); // gets the quantity
		void setAmountPurchased(int amountPurchased); // sets the quantity purchased
		int getAmountPurchased(); // gets the quantity purchased
		void setTotalCost(double totalCost); // sets the total cost of the denomination
		double getTotalCost(); // gets the total cost of the denominatiom
		void print(); // prints the main three attributes associated with the class
	private:
		string name; // name of the item
		int onHand; // quantity of the item
		double cost; // cost of the item
		int amountPurchased; // amount purchased of the item for ONE customer
		double totalCost; // total cost calculated for ONE customer
};


class Denom {
	public:
		Denom(); // constructor if no values are set
		Denom(int onHand, double cost, string name); // constructor that assigns the primary three attributes to Denom
		void setName(string); // sets the name
		string getName(); // gets the name
		void setCost(double); // sets the cost
		double getCost(); // gets the cost
		void setonHand(int); // sets the quantity
		int getonHand(); // gets the quantity
		void print(); // prints the main three attributes associated with the class
	private:
		string name; // name of the denomination
		int onHand; // quantity of the denomination
		double cost; // value of the denomination
};

void displayMenu(vector<Item> & items); // displays the menu of eleven items and a complete order option
void getProfit(vector<Denom> money, double & total); // calculates the end profit of the cash register
void giveChange(vector<Denom> & money, double & total, double & difference); // calculates the change after every purchase (if change is necessary)
void ItemSetter(Item item1, Item item2, Item item3, Item item4, Item item5, Item item6, Item item7, Item item8, Item item9, Item item10, Item item11, vector<Item> & items); // puts each item into a vector associated with its class
void makePayment(vector<Item> & items, vector<Denom> & money, double & total, double & difference); // user chooses which denominations to utilize for payment
void MenuFile(ifstream & Menu, string temp, string menu_strings[], vector<int> & Qnty, vector<double> & Price, vector<string> & itemName, string placeholder); // recovers three attributes of each menu item from a file
void MoneySetter(Denom Penny, Denom Nickels, Denom Dimes, Denom Quarters, Denom Dollar, Denom Five, Denom Ten, Denom Twenty, vector<Denom> & money); // sets each denomination into a vector associated with its class
void orderInfo(vector<Item> & items, double & total); // shows the quantity and name of each item purchased
void OrderItems(vector<Item> & items, double & total); // allows the user to choose items individually; order items
void orderStatus(bool & EndofDay, double total); // EndofDay Program: asks if there is another customer
void recoverQnty(fstream & Report); // recovers the information from the Report file to present at the end of the day
void sendQnty(vector <Item> & items, vector<Denom> & money, fstream & Report); // sends the information of denominations and items to the Report file

int main() {
	bool EndofDay = false;
	double total = 0, difference;
	vector <Denom> money;
	vector <Item> items;
	vector<int> Qnty;
	vector<double> Price;
	vector<string> itemName;
	Denom Penny(50, 0.01, "pennies"), Nickels(40, 0.05, "nickels"), Dimes(50, 0.10,"dimes"), Quarters(40, 0.25,"quarters"), Dollar (10, 1.00, "one dollar bills"), Five(10, 5.00, "five dollar bills"), Ten(10, 10.00,"ten dollar bills"), Twenty(0, 20.00,"twenty dollar bills");
	// Cash Register Starting Total: $0.50 + $2.00 + $5.00 + $10.00 + $10.00 + $50.00 + $100.00 + $0 --> $177.5
	ifstream Menu;
	fstream Report;
	string menu_strings[15], temp, placeholder;
	MenuFile(Menu, temp, menu_strings, Qnty, Price, itemName, placeholder);
	Item item1(Qnty[0], Price[0], itemName[0]), item2(Qnty[1], Price[1], itemName[1]), item3(Qnty[2], Price[2], itemName[2]), item4(Qnty[3], Price[3], itemName[3]), item5(Qnty[4], Price[4], itemName[4]), item6(Qnty[5], Price[5], itemName[5]), item7(Qnty[6], Price[6], itemName[6]), item8(Qnty[7], Price[7], itemName[7]), item9(Qnty[8], Price[8], itemName[8]), item10(Qnty[9], Price[9], itemName[9]), item11(Qnty[10], Price[10], itemName[10]);
	MoneySetter(Penny, Nickels, Dimes, Quarters, Dollar, Five, Ten, Twenty, money);
	ItemSetter(item1, item2, item3, item4, item5, item6, item7, item8, item9, item10, item11, items);
	do
	{
	total = 0;
	difference = 0;
	for (int i = 0; i < 11; i++) // Resets Values
	{
		items[i].setAmountPurchased(0);
		items[i].setTotalCost(0);
	}
	OrderItems(items, total);
	makePayment(items, money, total, difference);
	orderStatus(EndofDay, total);
	} while (EndofDay != true);
	sendQnty(items, money, Report);
	recoverQnty(Report);
	getProfit(money, total);
	return 0;
}

void displayMenu(vector<Item> & items)
{
	for (int i = 0; i < 11; i++)
	{
		if (items[i].getonHand() > 0)
		{
			cout << i + 1 << "] ";
			items[i].print();
			cout << endl;
		}
		else
		{
			cout << items[i].getName() << " UNAVAILABLE";
			cout << endl;
		}
	}
	cout << "12] COMPLETE ORDER";
}

void getProfit(vector<Denom> money, double & profit)
{
	double registeramt = 0;
	cout << "CASH REGISTER INFO" << endl;
	cout << "Register Started At: $177.50" << endl;

	for (int i = 0; i < 8; i++)
	{
		registeramt += (money[i].getCost() * money[i].getonHand());

	}
	cout << "Profit: $" << fixed << setprecision(2) << registeramt  - 177.5 << endl;
	cout << "Register Currently Holds: $" << fixed << setprecision(2) << registeramt << endl;
}

void giveChange(vector<Denom> & money, double & total, double & difference)
{
    vector<int> returnQnty(8, 0);
    int calculationValue, differenceValue, temp = 0, capLocation;
    string nameDisplay;
    differenceValue = (difference * 100) + 0.5; // +0.5 to deal with an issue where it's off by 1.
    cout << "Change Back: $" << fixed << setprecision(2) << difference << endl;

    for (int i = 7; i >= 0; i--)
    {
        nameDisplay = money[i].getName();
        if (money[i].getonHand() > 0)
        {
            calculationValue = (money[i].getCost() * 100);
            if (calculationValue <= differenceValue)
            {
            	returnQnty[i] = (differenceValue / calculationValue);
            	differenceValue = (differenceValue % calculationValue);
            	nameDisplay.at(0) = toupper(nameDisplay.at(0));
            	if (nameDisplay.length() > 10)
            	{
            		capLocation = nameDisplay.find("d");
            		nameDisplay.at(capLocation) = toupper(nameDisplay.at(capLocation));
            		capLocation = nameDisplay.find("b");
            		nameDisplay.at(capLocation) = toupper(nameDisplay.at(capLocation));
            	}
            	if ((money[i].getonHand() - returnQnty[i]) > 0)
            	{
            		cout << nameDisplay << ": " << returnQnty[i] << endl;
            		money[i].setonHand(money[i].getonHand() - returnQnty[i]); // qnty reduction
            	}
            	else
            	{
            		if ((money[i].getonHand() - returnQnty[i]) < 0)
            		{
            			temp = (returnQnty[i] - money[i].getonHand());
            			returnQnty[i] = money[i].getonHand();
            			differenceValue = (differenceValue) + (calculationValue * temp);
            			if ((money[i].getonHand() - returnQnty[i]) == 0)
            			{
            				cout << nameDisplay << ": " << returnQnty[i] << endl;
            				money[i].setonHand(money[i].getonHand() - returnQnty[i]);
            			}
            		}
            	}
            }
        }
    }
    temp = 0;
	for (int i = 7; i >= 0; i--)
    {
		calculationValue = (money[i].getCost() * 100);
		temp += (returnQnty[i] * calculationValue);
    }
	differenceValue = (difference * 100) + 0.5;
	if (temp != differenceValue)
	{
		cout << "Cash Register cannot distribute change." << endl;
		cout << "Ending Program..." << endl;
		exit(1);
	}
}

void ItemSetter(Item item1, Item item2, Item item3, Item item4, Item item5, Item item6, Item item7, Item item8, Item item9, Item item10, Item item11, vector<Item> & items)
{
	items.push_back(item1);
	items.push_back(item2);
	items.push_back(item3);
	items.push_back(item4);
	items.push_back(item5);
	items.push_back(item6);
	items.push_back(item7);
	items.push_back(item8);
	items.push_back(item9);
	items.push_back(item10);
	items.push_back(item11);
}

void makePayment(vector<Item> & items, vector<Denom> & money, double & total, double & difference)
{
	int option = 0, denomAmt;
	double inserted;
	do
	{
		cout << "Select a denomination to enter into the register: " << endl;
		cout << "1] Penny ($0.01)" << endl;
		cout << "2] Nickel ($0.05)" << endl;
		cout << "3] Dime ($0.10)" << endl;
		cout << "4] Quarter ($0.25)" << endl;
		cout << "5] Dollar Bill ($1.00)" << endl;
		cout << "6] Five Dollar Bill ($5.00)" << endl;
		cout << "7] Ten Dollar Bill ($10.00)" << endl;
		cout << "8] Twenty Dollar Bill ($20.00)" << endl;
		cin >> option;
		if (option >= 1 && option <= 8)
		{
			cout << "How many " << money[option - 1].getName() << " would you like to enter?" << endl;
			cin >> denomAmt;
			money[option - 1].setonHand(money[option - 1].getonHand() + denomAmt);
			inserted += (denomAmt * money[option - 1].getCost());
			cout << endl;
			cout << "You have entered " << denomAmt << " " << money[option - 1].getName() << "." << endl;
			if (inserted < total)
			{
				difference = total - inserted;
				cout << "Money Towards Total: $" << fixed << setprecision(2) << inserted << " | " << "Remaining Needed: $" << fixed << setprecision(2) << difference << endl;
			}
			else if (inserted >= total)
			{
				difference = inserted - total;
				cout << "Money Towards Total: $" << fixed << setprecision(2) << inserted << " | " << "Exceeded Total By: $" << fixed << setprecision(2) << difference << endl << endl;
				giveChange(money, total, difference);
			}
			cout << endl << endl;
		}
		else
		{
			cout << endl;
			cout << "Invalid Input.  Try Again." << endl << endl;
		}
	} while (total > inserted);
}

void MenuFile(ifstream & Menu, string temp, string menu_strings[], vector<int> & Qnty, vector<double> & Price, vector<string> & itemName, string placeholder)
{
	int size = 0, i, loc, loc2, vector_size;
	bool MoreData = true;
	Menu.open("Menu.txt");
	if (Menu.fail())
	{
		cout << "File could not be found" << endl;
		exit(1);
	}
	while (MoreData == true)
	{
		if (Menu.eof())
		{
			MoreData = false;
		}
		else
		{
			getline(Menu, temp);
			menu_strings[size] = temp;
			size++;
		}
	}

	for (i = 0; i < size; i++) // Converter
	{
		// Quantity Converter
		loc = 0;
		loc2 = menu_strings[i].find(" ");
		placeholder = menu_strings[i].substr(loc, loc2);
		Qnty.push_back(stoi(placeholder));

		// Price Converter
		loc = menu_strings[i].find(" ") + 1;
		loc2 = menu_strings[i].find(" ", loc, 1);
		placeholder = menu_strings[i].substr(loc, loc2 - loc);
		Price.push_back(stod(placeholder));

		// Name Converter
		loc = loc2 + 1;
		if (i == 8 || i == 5)
		{
			vector_size = menu_strings[i].size() - 1; // Overrides an error that adds 1 character to that line
		}
		else
		{
			vector_size = menu_strings[i].size();
		}
		loc2 = vector_size - loc;
		placeholder = menu_strings[i].substr(loc, loc2);
		itemName.push_back(placeholder);
	}
}

void MoneySetter(Denom Penny, Denom Nickels, Denom Dimes, Denom Quarters, Denom Dollar, Denom Five, Denom Ten, Denom Twenty, vector<Denom> & money)
{
	money.push_back(Penny);
	money.push_back(Nickels);
	money.push_back(Dimes);
	money.push_back(Quarters);
	money.push_back(Dollar);
	money.push_back(Five);
	money.push_back(Ten);
	money.push_back(Twenty);
}

void orderInfo(vector<Item> & items, double & total)
{
	vector<string> orderInfo;
	double priceValue = 0;
	cout << endl;
	cout << "--------------" << endl << endl;
	cout << "ORDER OVERVIEW" << endl << endl;
	for (int i = 0; i < 11; i++)
	{
		if (items[i].getAmountPurchased() > 0)
		{
			priceValue = items[i].getTotalCost();
			cout << items[i].getAmountPurchased() << " " << items[i].getName()  << " | $" << fixed << setprecision(2) << priceValue << endl;
		}
	}
	cout << "TOTAL: " << fixed << setprecision(2) << " $" << total << endl << endl;
}

void OrderItems(vector<Item> & items, double & total)
{
	int option, currentQnty;
	do
	{
		displayMenu(items);
		cout << endl << "Please enter your choice: ";
		cin >> option;
		if (option > 0 && option < 12)
		{
			cout << endl;
			if (items[option - 1].getonHand() > 0)
			{
				if (total + items[option - 1].getCost() >= 119.99)
				{
					cout << "Purchase Limit Reached" << endl;
					cout << "Total: $" << fixed << setprecision(2) << total << endl;
					cout << "Try Again." << endl << endl;
				}
				else
				{
					cout << items[option - 1].getName() << " added to cart" << endl;
					total += items[option - 1].getCost();
					cout << "Total: $" << fixed << setprecision(2) << total << endl << endl;
					currentQnty = items[option - 1].getonHand();
					items[option - 1].setonHand(currentQnty - 1);
					items[option - 1].setAmountPurchased(items[option - 1].getAmountPurchased() + 1);
					items[option - 1].setTotalCost((items[option - 1].getTotalCost() + items[option - 1].getCost()));
				}
			}
			else if (items[option - 1].getonHand() == 0)
			{
				cout << endl;
				cout << "You cannot purchase this item.  It is out of stock." << endl << endl;
			}
		}
		else if (option <= 0 || option > 12)
		{
			cout << endl;
			cout << "Invalid Option.  Try Again." << endl << endl;
		}
	} while (option != 12);
	orderInfo(items, total);
}

void orderStatus(bool & EndofDay, double total)
{
	int option;
	do
	{
		cout << "Is there another customer?" << endl;
		cout << "1] Yes" << endl;
		cout << "2] No" << endl;
		cin >> option;
		if (option != 1 && option != 2)
		{
			cout << "Invalid Input." << endl;
		}
	} while (option != 1 && option != 2);
	if (option == 2)
	{
		EndofDay = true;
	}
}

void recoverQnty(fstream & Report)
{
	bool MoreData = true;
    string line;
	Report.open("Report.txt");
	if (Report.fail())
	{
		cout << "File could not be found." << endl;
		exit(1);
	}
	while (MoreData == true)
	{
		if (!Report.eof())
		{
			getline(Report, line);
			cout << line << endl;
		}
		else
		{
			MoreData = false;
	    }
	}
	Report.close();
}

void sendQnty(vector<Item> & items, vector<Denom> & money, fstream & Report)
{
    Report.open("Report.txt");
    if (Report.is_open())
    {
    	cout << endl;
    	Report << "INVENTORY" << endl;
        for (int i = 0; i < 11; i++)
        {
        	Report << items[i].getName() << " | ";
        	Report << items[i].getonHand() << endl;
        }

        Report << endl;

        Report << "CASH REGISTER" << endl;
        for (int i = 0; i < 8; i++)
        {
        	string nameDisplay = money[i].getName();
        	int DLocation = nameDisplay.find("d");
        	int BLocation = nameDisplay.find("b");
        	nameDisplay[0] = toupper(nameDisplay[0]);
        	nameDisplay[DLocation] = toupper(nameDisplay[DLocation]);
        	nameDisplay[BLocation] = toupper(nameDisplay[BLocation]);
        	Report << nameDisplay << " | ";
        	Report << money[i].getonHand() << endl;
        }
    }
    Report.close();
}

Denom :: Denom ()
{
	this->onHand = 0;
	this->cost = 0.00;
	this->name = "No Name";
}

Denom :: Denom (int onHand, double cost, string name)
{
	this->onHand = onHand;
	this->cost = cost;
	this->name = name;
}

void Denom :: setName(string name)
{
	this->name = name;
}

string Denom :: getName()
{
	return name;
}

void Denom :: setCost(double cost)
{
	this->cost = cost;
}

double Denom :: getCost()
{
	return cost;
}

void Denom :: setonHand(int onHand)
{
	this->onHand = onHand;
}

int Denom :: getonHand()
{
	return onHand;
}

void Denom :: print()
{
	cout << name << " " << cost << " " << onHand;
}

Item :: Item ()
{
	this->onHand = 0;
	this->cost = 0.00;
	this->name = "Unknown Name";
	this->amountPurchased = 0;
	this->totalCost = 0.0;
}

Item :: Item (int onHand, double cost, string name)
{
	this->onHand = onHand;
	this->cost = cost;
	this->name = name;
	this->amountPurchased = 0;
	this->totalCost = 0.0;
}

void Item :: setName(string name)
{
	this->name = name;
}

string Item :: getName()
{
	return name;
}

void Item :: setCost(double cost)
{
	this->cost = cost;
}

double Item :: getCost()
{
	return cost;
}

void Item :: setonHand(int onHand)
{
	this->onHand = onHand;
}

int Item :: getonHand()
{
	return onHand;
}

void Item :: setAmountPurchased(int amountPurchased)
{
	this->amountPurchased = amountPurchased;
}

int Item :: getAmountPurchased()
{
	return amountPurchased;
}

void Item :: setTotalCost(double totalCost)
{
	this->totalCost = totalCost;
}

double Item :: getTotalCost()
{
	return totalCost;
}

void Item :: print()
{
	cout << name << " $" << fixed << setprecision(2) << cost << " | " << onHand;
}




