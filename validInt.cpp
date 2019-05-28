/***************************************
Program Name: Project 1
Author: Robert Elsom
Date: 1/10/2019
Description: Checks that inputted integer from the menu function
			fits in the parameters of the program. If 
			it does, it returns the integer that was tested.
**************************************/

#include <string>
#include <iostream>
#include <ctype.h>

using std::cout;
using std::cin;
using std::endl;
using std::string;

int validInt( string prompt, int lowerLimit, int upperLimit)	{
	int testInteger;
	bool validFlag = false;
	bool isNumber = true;
	string choice;

	while(validFlag == false)	{
		cout << prompt;
		cin >> choice;

		//changes flag isNumber if any part of input is not a digit
		for (unsigned int i = 0; i <choice.length(); i++)    {
			if (!isdigit(choice[i]))    {
			   isNumber = false;
			}
		}

		if(!isNumber)   {
			cout<< "Sorry, that is not a valid input" << endl;
			isNumber= true;
		}

		//if variable choice passes as being a number, now verify that it is in range and
		//fit in the limits of the program parameters
		else   {
			testInteger = stoi(choice);

			if (testInteger > upperLimit)	{
				cout << "Sorry, that number is too large" << endl;
			}
			else if (testInteger < lowerLimit)	{
				cout << "Sorry, that number is too small"<< endl;
			}
			else{
				validFlag = true;
			}
		}
	}

	return testInteger;
	
}
