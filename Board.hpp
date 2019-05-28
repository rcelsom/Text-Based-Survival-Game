/***************************************
Program Name: Final Project
Author: Robert Elsom
Date: 3/6/2019
Description: Board class header file
**************************************/
#include <string>
#include "Space.hpp"
#ifndef BOARD_HPP
#define BOARD_HPP
class Board	{
private:
	Space* head = nullptr;
	Space* prevSpace = nullptr;
	Space* headRow = nullptr;
	Space* aboveSpace = nullptr;
	Space* character = nullptr;
	Space* exitSpace = nullptr;
	bool printExit = false;
	int characterCol;
	int characterRow;
public:
	Board();
	void addNode(Space*, int , int);
	void fillBoard(int, int);
	void printBoard();
	void errorMessage();
	void makeCharacter();
	void moveCharacter();
	void moveCharacterUp();
	void moveCharacterDown();
	void moveCharacterLeft();
	void moveCharacterRight();
	void moveCharacterShelter(Space* );
	int getCharacterCol();
	int getCharacterRow();
	Space* getCharacterSpace();
	Space* getHead();
	bool printExitSpace();
	void setPrintExit();
	void setExit();
	Space* getExitSpace();
	~Board();
	
	
};
#endif