/***************************************
Program Name: Final Project
Author: Robert Elsom
Date: 3/6/2019
Description: Creek class, allows character to drink to replenish water bar.
**************************************/
#include "Creek.hpp"
#include <iostream>
#include "validStr.hpp"

std::string Creek::getType()	{
	return "creek";
}

//checks if character got sick from water, 20% chance of getting sick and losing time. 
bool Creek::gotSick()	{
	
	if (rand()%100 < 20)	{
		return true;
	}
	else	{
		return false;
	}
}

//fills canteen if user chooses to
int Creek::enterSpace(int waterLevel)	{
	std::string choice = validStr("You just found a creek! Would you like to refill your canteen? (Y/N) \n");
	
	if (choice == "Y" || choice == "y")	{
		std::cout << "You just found water to fill your canteen! Your water level is now full!" << std::endl;
		return 100;
	}
	else	{
		std::cout << "This water will be here whenever you need to refill your canteen next time!" << std::endl;
		return 0;
	}
}
