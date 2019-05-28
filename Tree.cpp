/***************************************
Program Name: Final Project
Author: Robert Elsom
Date: 3/6/2019
Description: Tree class, allows character to collect wood in order to 
			build shelters which function as check points or fire to help
			reduce chance of hypothermia at night
**************************************/
#include <cstdlib>
#include "Tree.hpp"
#include <iostream>
#include "validStr.hpp"

int Tree::enterSpace(int totalWood)	{
	int woodAmount = 0;
	
	//collect wood if first time in square
	if (!alreadyEntered)	{
		std::string choice = validStr("Would you like to explore the area and collect wood? (Y/N)\n");
		if (choice == "Y" || choice == "y")	{
			alreadyEntered = true;
			woodAmount = rand() % 25 + 1;
		}
		else	{
			std::cout << "You have not found any wood to add to your pack." << std::endl;
		}
	}
	else	{
		std::cout << "You already entered this wooded area, nothing new to find here. " <<std::endl;
	}
	
	return woodAmount;
}

void Tree::setEntered()	{
	alreadyEntered = false;
}

bool Tree::haveEntered()	{
	return alreadyEntered;
}

std::string Tree::getType()	{
	return "tree";
}

int Tree::returnWood()	{
	return (rand() % 25) + 1;
}

