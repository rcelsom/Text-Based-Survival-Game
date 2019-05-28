/***************************************
Program Name: Final Project
Author: Robert Elsom
Date: 3/6/2019
Description: Tree class header file
**************************************/
#include <string>
#include "Space.hpp"

#ifndef TREE_HPP
#define TREE_HPP
class Tree: public Space	{
private:
	bool alreadyEntered = false;
	
public:

	std::string getType();
	int enterSpace(int);
	bool haveEntered();
	int returnWood();
	void setEntered();
};
#endif