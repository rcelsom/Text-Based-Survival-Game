/***************************************
Program Name: Final Project
Author: Robert Elsom
Date: 3/6/2019
Description: Cabin class, contains a represented cabin for
			the character to enter, which takes them to a new board
			Inside the board (inside cabin) they must search for a key to
			a chest which contains a map to lead them out of the woods
**************************************/
#include "Cabin.hpp"
#include "validStr.hpp"
#include <string>
#include <iostream>

std::string Cabin::getType()	{
	return "cabin";
}

//pass key parameter only to make it fit virtual space function, do not need in parameter
int Cabin::enterSpace(int numKeys)		{
	if (!hasEntered)	{
		std::string choice = validStr("You just found the remnants of an old cabin! Unfortunatly it does not look stable enough to live in.\n"\
									  "Would you like to enter the cabin and explore? (Y/N)\n");

		if (choice == "Y" || choice == "y")	{
			hasEntered = true;
			return 5;

		}
		else	{
			std::cout << "You left the creepy cabin alone, you must watch horror movies. You can return at any time." << std::endl;
		}
	}
	else	{
		std::cout << "You returned to the creepy cabin. There is nothing new to find here." << std::endl;
	}
	return 0;
}


		
