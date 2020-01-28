/***************************************
Program Name: Final Project
Author: Robert Elsom
Date: 3/6/2019
Description: Space class, contains 2d linked list representing board spaces
			with 4 space pointers for up, left, down, and right. 
			
**************************************/
#include "Space.hpp"
#include <curses.h>
#include <iostream>

/*
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
*/

Space::Space()	{ 
	right = nullptr;
	left = nullptr;
	up = nullptr;
	down = nullptr;
}

//changes pointers
void Space::changePointer(Space* newPtr, std::string direction)	{
	if (direction == "up")	{
		up = newPtr;
	}
	else if (direction == "down")	{
		down = newPtr;
	}
	else if (direction == "left")	{
		left = newPtr;
	}
	else	{
		right = newPtr;		
	}
}

//returns pointer for specific direction
Space* Space::getPointer(std::string direction)	{
	if (direction == "up")	{
		return up;
	}
	else if (direction == "down")	{
		return down;
	}
	else if (direction == "left")	{
		return left;
	}
	else	{
		return right;		
	}
}

//remaining functions are here just to be used with derived classes, add nothing to actual space class
bool Space::hasShelter()	{
	return false;
}

bool Space::gotHypothermia()	{
	return false;
}

void Space::buildShelter()	{}

void Space::setEntered()	{}
Space::~Space()		{
	
}
