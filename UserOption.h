#pragma once
#include <string>
#include <vector>
#include "OrderBook.h"
#include "OrderBookEntry.h"

class UserOption
{

public:
	UserOption();

	void init();
	std::string getUserCommand();



	// Parsing of user command in to different tokens and sent for validation in respective functions
	void processUserCommand(std::vector<std::string> words);
	std::vector<std::string> parseUserInput(std::string userInput);
	std::vector<std::string> words;


	// C1 - help
	void help(); 

	// C2 - help cmd
	void helpCmd(std::string);
	
	// C3 - prod
	void prod();

	// C4 - min
	void min(std::string ordertype, std::string product);

	// C5 - max
	void max(std::string ordertype, std::string product);

	// C6 - avg

	void average(std::string prod, std::string orderTpe, std::string timesteps);

	// C7 - predict
	double predict(std::string type, std::string prod, std::string orderTpe);
	
	// C8 - time
	void printCurrentTime();

	// C9 - step
	void step();
	
	// Task 2: Own Command
	void trend(std::string prod, std::string orderTpe, std::string timesteps);

	int grabCurrentIndex();
	
	
	

};