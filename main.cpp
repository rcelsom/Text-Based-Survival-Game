#include "Game.hpp"
#include "Space.hpp"
#include <iostream>

int menu ()	{
	std::cout << "\n\nWelcome to a Wilderness Survival Game." << std::endl<<std::endl;
	std::cout << "The goal is to figure out how to exit the woods before a tornado hits and return back to your\n"\
				"life in civilization.\n" << std::endl << std::endl;
	std::cout << "You can collect wood near trees to make shelters and fires in the grassy areas.\n"\
				"You can also drink water from the creek beds. There is even a special space to explore that \n"\
				"may contain very useful items." << std::endl << std::endl;
	
	std::cout << std::endl <<"You have 3 days and 2 nights, with 7 hours of daylight to find wood, collect water, and explore. \n"\
				"Each space takes exactly one hour to move across, and once out of daylight, you will\n"\
				"automatically return to your nearest shelter." <<std::endl << std::endl;
	
	std::cout << std::endl << "You need to make sure to maintain you water levels and you should be worried\n"\
				"about hypothermia during the night. Luckily, there are ways to avoid those." << std::endl << std::endl;
	
	std::string userChoice = validStr("\nWould you like to play this game? (Y/N) \n");
	if (userChoice == "Y" || userChoice == "y")	{
		return 1;
	}
	return 0;
}
	
int main()	{
	srand(time(NULL));
	int choice = menu();
	if (choice == 1)	{
		Game game;
	}
}