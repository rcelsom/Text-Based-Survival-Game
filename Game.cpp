/***************************************
Program Name: Final Project
Author: Robert Elsom
Date: 3/6/2019
Description: Game class, responsible for making the board and carrying out the actual gameplay.
**************************************/
#include <iostream>
#include <cmath>

#include "Game.hpp"
#include "Space.hpp"
#include "Creek.hpp"
#include "Tree.hpp"
#include "Cabin.hpp"
#include "validStr.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::string;

//constructor creates character, fills backpack and also sets max amount of items in maxBackpackCapacity
Game::Game()	{
	backpack["wood"] = 0;
	backpack["water"] = 100;
	backpack["matches"] = 0;
	backpack["keys"] = 0;

	round();
}

//simulates rounds until time runs out or user wins
void Game::round()	{
	printMap();
	while(!gameFinished)	{
		updateWater(-14);
		//check if ran out of water if not moving to a water space
		if ((board.getCharacterSpace())->getType() == "water")	{
			checkWaterLevel();
		}
		board.moveCharacter();
		printMap();

		interactWithSpace();
		if (!gameFinished)	{
			checkWaterLevel();
			updateTime();
		}
		
	}
	printFinalResults();
}

//updates time and checks if need to go to next day or out of time
void Game::updateTime()		{
	timeCounter++;

	//if MAX_TIME hours pass, return to shelter and increase dayCounter 
	if (timeCounter == MAX_TIME)	{
		dayCounter++;
		timeCounter = 0;
		if (dayCounter > MAX_DAYS)	{
			std::cout << "\n\nOh no! You ran out of time to exit the woods! A tornado just destroyed everything, including you!" << std::endl;
			gameFinished = true;
		}
		else	{
			moveNearestShelter();
		}
	}
	if (!gameFinished)	{
		printResultsHour();
	}
}
		
//moves character to nearest shelter
void Game::moveNearestShelter()	{
	Space* nearestShelter = nullptr;
	
	//if not already in a shelter
	if (!((board.getCharacterSpace())->hasShelter()))	{
		std::cout << "\nYou ran out of daylight. You are about to return to your nearest shelter." << std::endl;
		//pause before displaying new screen
		std::cout << "Press enter to continue playing..." << std::endl;
		std::cin.ignore();
		std::cin.get();


		
		nearestShelter = getNearestShelter();
	}
			
	//moves character to nearest shelter if there is one and test if user got hypothermia
	if (nearestShelter != nullptr)	{
		board.moveCharacterShelter(nearestShelter);
		board.printBoard();
		std::cout << "You returned to a shelter for the night." << std::endl;
		makeFire();
	}
}

//calculates nearest shelter distance
Space* Game::getNearestShelter()	{
	Space* nearestShelter = NULL;
	Space* temp = board.getHead();
	Space* headRow = board.getHead();

	double distance = 0.0;
	double shortestDistance = -1.0;
	
	//loops through 2d linked list board in order to find all shelters
	for (int i = 0; i < 5; i++)	{
		for (int j = 0; j < 5; j++)	{
			//finds shelters
			if (temp->hasShelter()) 	{
				distance = calculateDistance(j, i);
				shortestDistance = updateMinDistance(temp, nearestShelter, distance);
			}
			//moves to next spot on board
			temp = temp->getPointer("right");
		}
		//move to next row
		headRow = headRow->getPointer("down");
		temp = headRow;
	}
	return nearestShelter;
}

int Game::updateMinDistance(Space* currentSpace, Space* nearestShelter, int distance)	{
	if (distance <= shortestDistance || shortestDistance == -1.0)	{
		shortestDistance = distance;
		nearestShelter = currentSpace;
	}
	
}

//calculates if user can build fire, then prompts to build a fire
void Game::makeFire()	{
	if (backpack.at("wood") > 3 && backpack.at("matches") > 0)	{
		std::string userChoice = validStr( "Would you like to build a fire to reduce hypothermia for 4 pieces of wood and 1 match? (Y/N)");
		updateWood(-4);
		backpack.at("matches") -= 1;
		if (userChoice == "N" || userChoice == "n")	{
			gameFinished = (board.getCharacterSpace())->gotHypothermia();
		}
	}
	else if (backpack.at("wood") <= 0)	{
		std::cout << "Unfortunately, you do not have enough wood for a fire to eliminate the chances of hypothermia."<<std::endl;
		gameFinished = (board.getCharacterSpace())->gotHypothermia();
	}
	else 	{
		std::cout << "Unfortunately, you do not have any way to start a fire to eliminate the chances of hypothermia."<<std::endl;
		gameFinished = (board.getCharacterSpace())->gotHypothermia();
	}
	
	if (!gameFinished)	{
			std::cout << "\nYou dodged hypothermia and survived the night!" << std::endl;
	}
}

//calculates distance from shelter to spot located at col, row
double Game::calculateDistance(int col, int row)	{
	return sqrt(pow((board.getCharacterCol() - col),2) + pow((board.getCharacterRow() - row),2));
}

//calls enterSpace from certain space types passing needed parameter
void Game::interactWithSpace()	{
	int tempInt = 0;
	//if the character is in the space to win the game
	if (board.getCharacterSpace() == board.getExitSpace())	{
		board.setPrintExit();
		interactWithCar(backpack.at("keys"));
	}
	else if (board.getCharacterSpace()->getType() == "creek")	{
		tempInt = (board.getCharacterSpace())->enterSpace(backpack.at("water"));
		updateWater(tempInt);
	}
	else if (board.getCharacterSpace()->getType() == "cabin")	{
		tempInt = (board.getCharacterSpace())->enterSpace(backpack.at("matches"));
		updateMatches(tempInt);
		addToBackpack("keys", 1);
		board.setPrintExit();
	}
	else 	{
		tempInt = (board.getCharacterSpace())->enterSpace(backpack.at("wood"));
		updateWood(tempInt);
	}
}

void Game::interactWithCar(int key)	{
	if (key == 1)	{
		std::string finalChoice = validStr("You found a car! Would you like to use your key to see if it starts? (Y/N)");
		if (finalChoice == "Y" || finalChoice =="y")	{
			gameFinished = true;
			wonGame = true;	
			std::cout << "\nThe car started! You used it to return to civilization!" << std::endl << std::endl;
		}
		else	{
			std::cout << "Ok. Continue searching on a way to leave the woods!" << std::endl << std::endl;
		}
	}
	else	{
		std::cout << "You found a car! If only you had a key to start it up!" << std::endl;
		board.setPrintExit();
		std::cout << "After this turn, it will be marked on your map with a XX symbol" << std::endl;
	}
}

void Game::addToBackpack(std::string key, int value)	{
	backpack.at(key) += value;
}

void Game::printMap()	{
	board.printBoard();
}



void Game::printResultsHour()	{
	std::cout << std::endl << std::endl << "---------Hourly Results---------" << std::endl;
	std::cout << "Current Backpack contents: " << std::endl;
	std::cout << "Wood:  " << backpack.at("wood") << std::endl;
	std::cout << "Water Remaining:  " << backpack.at("water") << "%" <<  std::endl;
	std::cout << "Number of matches:  " << backpack.at("matches") << std::endl;
	std::cout << "Number of keys:  " << backpack.at("keys") << std::endl;
	std::cout << std::endl << "Hours remaining in day:   " << MAX_TIME - timeCounter << std::endl;
	std::cout << "Days remaining:   " << MAX_DAYS-dayCounter <<std::endl;
}

void Game::printFinalResults()	{
	if (wonGame)	{
		std::cout << "\n\nYOU WON! You survived and excelled in the woods!" << std::endl;
	}
	
	std::cout << std::endl << std::endl << "---------Final Results---------" << std::endl;
	if (wonGame)	{
		std::cout << "YOU ARE A WINNER!!!!!"<<std::endl <<std::endl;
	}
	else	{
		std::cout << " YOU LOST! You did not survive the woods!" << std::endl << std::endl;
	}
	std::cout << "Current Backpack contents: " << std::endl;
	std::cout << "Wood:  " << backpack.at("wood") << std::endl;
	std::cout << "Water Remaining:  " << backpack.at("water") << "%" <<  std::endl;
	std::cout << "Number of matches:  " << backpack.at("matches") << std::endl;
	std::cout << "Number of keys:  " << backpack.at("keys") << std::endl;
	std::cout << std::endl << "Days lasted:   " << dayCounter-1 << std::endl;
	std::cout << "Hours lasted:   " << timeCounter <<std::endl <<std::endl << std::endl;
		
}

//updates water in backpack
void Game::updateWater(int newNum)	{
	//make sure not exceding max capacity of water
	if (newNum + backpack.at("water") > maxCapacity.at("water"))	{
		newNum = maxCapacity.at("water")-backpack.at("water");
	}
	if (newNum + backpack.at("water") < 0)	{
		newNum = 0 - backpack.at("water");
	}
	backpack.at("water") += newNum;
}

//checks if water is empty
void Game::checkWaterLevel()	{
	if (backpack.at("water") <= 0)	{
		std::cout << std::endl << "Oh no, you ran out of water and died!" << std::endl;
		gameFinished = true;
	}
}

//udpates wood in backpack
void Game::updateWood(int newNum)	{
	std::string key = "wood";
	if (newNum + backpack.at(key) > maxCapacity.at(key))	{
		newNum = maxCapacity.at(key) - backpack.at(key);
		if (newNum == 0)	{
			(board.getCharacterSpace())->setEntered();
			std::cout << "Sorry, you have too much wood already. Nothing was added to your backpack." <<std::endl;
		}
	}
	else if (newNum + backpack.at(key) < 0)	{
		newNum = 0 - backpack.at(key);
	}
	if ((board.getCharacterSpace())->getType() == "tree" && newNum != 0)	{
		std::cout << "You just entered the woods and found " << newNum;
		std::cout << " pieces of wood to add to your backpack!" << std::endl;
	}
	backpack.at(key) += newNum;
}

//updates matches in backpack
void Game::updateMatches(int newNum)	{
	std::string key = "matches";
	if (newNum + backpack.at(key) > maxCapacity.at(key))	{
		newNum = maxCapacity.at(key) - backpack.at(key);
		
	}
	else if (newNum + backpack.at(key) < 0)	{
		newNum = 0 - backpack.at(key);
	}
	if ((board.getCharacterSpace())->getType() == "cabin" && newNum != 0)	{
		std::cout << "You just entered the cabin and found " << newNum;
		std::cout << " matches to add to your backpack!" << std::endl;
	}
	backpack.at(key) += newNum;
	std::cout << std::endl << "You also found car keys and a map to the car! It will be marked with XX on your next turn!" << std::endl;
	board.setExit();
}
	