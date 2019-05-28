/***************************************
Program Name: Final Project
Author: Robert Elsom
Date: 3/6/2019
Description: Board class, conatains 2d linked list of Space objects and derived Space objects
			represents the game board. 
**************************************/
#include "Board.hpp"
#include "Space.hpp"
#include "Creek.hpp"
#include "Tree.hpp"
#include "Cabin.hpp"
#include "Grass.hpp"
#include "validInt.hpp"
#include <iostream>
#include <curses.h>
#include <cstdlib>

//make initial game board 5x5
Board::Board()	{
	for (int i = 0; i < 5; i++)	{
		for (int j = 0; j < 5; j++)	{
			fillBoard(j, i);
		}
	}
	makeCharacter();
	setExit();
	printBoard();
}


//creates nodes to fill board and the uses addNode to add new nodes to board. 
void Board::fillBoard(int col, int row)	{
	Space* newPtr;
	//puts cabin at space 1,1
	if (row == 1 && col == 1)	{
		newPtr = new Cabin();
	}
	//makes row 3 a creek
	else if (row == 3)	{
		newPtr = new Creek();
	}
	//makes a forest surrounding the cabin and one past the creek
	else if ((row <= 2 && col < 4-row) || (row == 4 && col < 1))	{
		newPtr = new Tree();
	}
	//fills rest of board as grass;
	else	{
		newPtr = new Grass();
	}
	addNode(newPtr, col, row);
}

//adds node to board and changes surrounding pointers
void Board::addNode(Space* newPtr, int col, int row)	{
	//set head
	if (row == 0 && col == 0)	{
		head = newPtr;
		headRow = head;
		aboveSpace = headRow;
	}
	
	Space* tempPtr;
	
	//set left pointer for second element that does not have a current left pointer
	if(col == 1)	{
		newPtr->changePointer(headRow, "left");
		headRow->changePointer(newPtr, "right");
	}
	//use tempPtr to move all pointers from other spaces to the new space
	else if(col > 1)	{
		tempPtr = prevSpace;
		tempPtr->changePointer(newPtr, "right");
		newPtr->changePointer(tempPtr, "left");
	}

	//set each row's first element pointers to head and move headRow down
	if (row >= 1 && col == 0)	{
		aboveSpace = headRow;
		headRow->changePointer(newPtr, "down");
		newPtr->changePointer(aboveSpace, "up");
		//sets head row to first element in second row

		headRow = headRow->getPointer("down");
		
	}
	else if (row >= 1 && col != 0)	{		
		aboveSpace = aboveSpace->getPointer("right"); 
		aboveSpace->changePointer(newPtr, "down");
		newPtr->changePointer(aboveSpace, "up");  
	}
	prevSpace = newPtr;
}

//makes character that represents the person the user is moving, starts at positon 2,2
void Board::makeCharacter()	{
	Space* temp = head;
	for (int i = 0; i < 2; i++)	{
		temp = temp->getPointer("down");
		temp = temp->getPointer("right");
	}
	character = temp;
	temp->buildShelter();
	characterCol = 2;
	characterRow = 2;
}

//move character to new space based on user input
void Board::moveCharacter()	{
	int choice = validInt("\n\nWhich direction would you like to move?\n"\
						  " 1. Up \n 2. Down \n 3. Left \n 4. Right\n", 1, 4);
	switch(choice) {
	case 1:
		moveCharacterUp();
		return;
	case 2:
		moveCharacterDown();
		return;
	case 3:
		moveCharacterLeft();
		return;
	case 4:
		moveCharacterRight();
		return;
		
	}
}

//moves character up
void Board::moveCharacterUp()	{
	if (character->getPointer("up") != nullptr)	{	
		character = character->getPointer("up");
		characterRow -= 1;
	}
	else	{
		errorMessage();
	}
}

//moves character down
void Board::moveCharacterDown()	{
	if (character->getPointer("down") != nullptr)	{	
		character = character->getPointer("down");
		characterRow += 1;
	}
	else	{
		errorMessage();
	}
}

//moves character  left
void Board::moveCharacterLeft()	{
	if (character->getPointer("left") != nullptr)	{	
		character = character->getPointer("left");
		characterCol -= 1;
	}
	else	{
		errorMessage();
	}
}

//moves character right
void Board::moveCharacterRight()	{
	if (character->getPointer("right") != nullptr)	{	
		character = character->getPointer("right");
		characterCol += 1;
	}
	else	{
		errorMessage();
	}	
}

//moves character to nearest shelter pointer
void Board::moveCharacterShelter(Space* shelter)	{
	character = shelter;
}

//returns space character is occupying
Space* Board::getCharacterSpace()	{
	return character;
}

//returns col character is currently in
int Board::getCharacterCol()	{
	return characterCol;
}

//returns row character is currently in
int Board::getCharacterRow()	{
	return characterRow;
}

//sets exit pointer to bottom left corner
void Board::setExit()	{
	Space* temp = head;
	for (int i = 0; i < 4; i++){
		temp = temp->getPointer("down");
		temp = temp->getPointer("right");
	}
	exitSpace = temp;
}

//returns location of head
Space* Board::getHead()	{
	return head;
}

//returns the exitSpace pointer
Space* Board::getExitSpace()	{
	return exitSpace;
}

//sets flag to print instructions in exit square
void Board::setPrintExit()	{
	printExit = true;
}

//returns flag if it is time to print exit
bool Board::printExitSpace()	{
	return printExit;
}

//prints error when trying to move character out of play area
void Board::errorMessage()	{
	printBoard();
	std::cout << "Sorry, you cannot move any further in that direction" << std::endl;
	moveCharacter();
}

//display board
void Board::printBoard()	{

	//cheap clear screen
	for (int i = 0; i < 50; i++)	{
		std::cout << std::endl;
	}
	//sets board symbols
	std::string tree = " $$ ";
	std::string cabin = " ?! ";
	std::string grass = " __ ";
	std::string shelter = " /| ";
	std::string creek = "===="	;
	std::cout << "-----------------MAP-----------------" << std::endl;
	Space* temp;
	Space* headRow = head;
	
	//prints board
	for (int i = 0; i < 5; i ++)	{
		temp = headRow;
		std::cout << "       |";
		for (int j = 0; j < 5; j++)	{
			if (temp == character)	{
				std::cout << " ## ";
			}
			else if(temp == exitSpace && printExit)	{
				std::cout << " XX ";
			}
			else if (temp->getType() == "creek")	{
				std::cout << creek;
			}
			else if (temp->getType() == "cabin")	{
				std::cout << cabin;
			}
			else if (temp->getType() == "tree")	{
				std::cout << tree;
			}
			else if (temp->getType() == "grass")	{
				if (temp->hasShelter())	{
					std::cout << shelter;
				}
				else	{
					std::cout << grass;
				}
			}
			temp = temp->getPointer("right");
		}
		std::cout << "|" << std::endl;
		headRow = headRow->getPointer("down");
	}
	//print key describing board
	std::cout <<"_____________________________________" << std::endl;
	std::cout << "               KEY                  "<<std::endl;
	std::cout << "  $$ = trees          __ = grass    " <<std::endl;
	std::cout << "  /| = shelter       ==== = creek   " << std::endl;
	std::cout << "  ## = position of character        " << std::endl;
	std::cout <<"_____________________________________" << std::endl;
	
	//print blank lines for spacing
	for (int i = 0; i < 10; i++)	{
		std::cout << std::endl;
	}
}

Board::~Board()	{
	Space* garbage = head->getPointer("right");
	headRow = head;
	for (int j = 0; j < 5; j++)	{
		for (int i = 0; i < 4; i++)	{
			Space* temp = garbage->getPointer("right");
			delete garbage;
			garbage = temp;
		}
		garbage = headRow;
		headRow = headRow->getPointer("down");
		delete garbage;
		if (headRow != nullptr)	{
			garbage = headRow->getPointer("right");
		}
	}
}


