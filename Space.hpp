/***************************************
Program Name: Final Project
Author: Robert Elsom
Date: 3/6/2019
Description: Space class header file, base class
**************************************/
#include <string>

#ifndef SPACE_HPP
#define SPACE_HPP

class Space	{
protected:

	Space* right;
	Space* left;
	Space* up;
	Space* down;
		
		
	
	Space* head = nullptr;
	Space* Character = nullptr;
	int characterRow=0;
	int characterCol=0;

public:
	Space();
	virtual ~Space();
	virtual std::string getType() = 0;
	virtual int enterSpace(int ) = 0;
	virtual bool gotHypothermia();
	virtual void buildShelter();
	Space* getPointer(std::string);
	void changePointer(Space*, std::string);
	virtual bool hasShelter();
	virtual void setEntered();
	

};
#endif