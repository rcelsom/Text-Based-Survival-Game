/***************************************
Program Name: Final Project
Author: Robert Elsom
Date: 3/6/2019
Description: Grass class header file
**************************************/
#include <string>
#include "Space.hpp"

#ifndef GRASS_HPP
#define GRASS_HPP
class Grass: public Space	{
private:
	bool builtShelter = false;
	bool builtFire;
	bool hypothermia = false;
	
public:
	int enterSpace(int );
	std::string getType();
	bool hasShelter();
	void sleepSpace();
	bool gotHypothermia();
	bool getHypothermiaFlag();
	void makeSpace(Space* ptr, int col, int row);
	int buildShelter(int );
	void buildFire();
	void extinguishFire();
	bool hasFire();
};
#endif