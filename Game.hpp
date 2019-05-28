/***************************************
Program Name: Final Project
Author: Robert Elsom
Date: 3/6/2019
Description: Game header file
**************************************/


#include <string>
#include <iostream>
#include <map>
#include "Space.hpp"
#include "Grass.hpp"
#include "Board.hpp"
#include "validStr.hpp"

#ifndef GAME_HPP
#define GAME_HPP
class Game	{
private:
	const int MAX_TIME = 7;
	const int MAX_DAYS = 3;
	int timeCounter = 0;
	int dayCounter = 1;
	bool hypothermia = false;
	Board board;
	bool gameFinished = false;
	bool wonGame = false;
	std::map<std::string, int> backpack;
	std::map<std::string, int> maxCapacity{{"matches", 5}, {"wood", 50}, {"water", 100}};
	
public:
	//fills backpack and maxBackpackCapactity
	Game();
	void updateTime();
	void moveNearestShelter();
	Space* getNearestShelter();
	int updateMinDistance(Space*, Space*, int);
	double calculateDistance(int, int);
	void interactWithSpace();
	void interactWithCar(int);
	void makeFire();
	void addToBackpack(std::string, int);
	
	void printMap();
	void round();
	void printResultsDay();
	void endOfDay();
	void printResultsHour();
	void printFinalResults();

	void updateWater(int );
	void checkWaterLevel();
	void updateWood(int );
	void updateMatches(int);

	
};
#endif