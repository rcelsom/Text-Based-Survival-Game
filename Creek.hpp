/***************************************
Program Name: Final Project
Author: Robert Elsom
Date: 3/6/2019
Description: Creek class header file
**************************************/

#include <string>
#include "Space.hpp"

#ifndef CREEK_HPP
#define CREEK_HPP
class Creek: public Space	{
private:

	
public:
	std::string getType();
	bool gotSick();
	int enterSpace(int);
	
};
#endif