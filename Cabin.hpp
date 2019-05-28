/***************************************
Program Name: Final Project
Author: Robert Elsom
Date: 3/6/2019
Description: Cabin class header file
**************************************/
#include <string>
#include "Space.hpp"

#ifndef CABIN_HPP
#define CABIN_HPP

class Cabin: public Space	{
private:
	bool hasEntered = false;
	
public:
	std::string getType();
	int enterSpace(int numKeys);
};
#endif