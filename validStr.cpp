/***************************************
Program Name: Project 1
Author: Robert Elsom
Date: 1/10/2019
Description: Checks that inputted string from the menu function
			fits in the parameters of the program. If 
			it does, it returns the string that was tested.
**************************************/

/**********************************************
Test case 1 = starting menu prompt
	to reuse: change number of menu options
			  update if statement to contain all options

Test case 2 = Y or N question
	to reuse: no changes necessary
**********************************************/
#include <string>
#include <iostream>
#include <ctype.h>

using std::cout;
using std::cin;
using std::endl;
using std::string;

string validStr(string prompt)	{
	string testString;
	bool validFlag = false;
	string userChoice;


	while (validFlag == false)	{
		cout << prompt << endl;
		cin >> userChoice;

		if (userChoice == "Y" || userChoice == "y" || userChoice == "N" || userChoice == "n")	{
			validFlag = true;
			return userChoice;
		}
		else	{
			cout << "Sorry, that is not a valid option. Please enter Y for yes or N for no." << endl;

		}
	}
	return "";
}