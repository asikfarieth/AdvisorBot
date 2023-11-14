#include "AdvisorMain.h"
#include <iostream>
#include <string>
#include <vector>
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include "OrderBook.h"
#include "UserOption.h"

//int global_test;

std::string currentTime;
OrderBook orderBook{"20200601.csv"};

AdvisorMain::AdvisorMain()
{



}
// Initialize the advisorbot constructor and start running via init
void AdvisorMain::init() {
	
	std::cout << "Welcome to Advisorbot.\n" << std::endl;

	std::cout << "Advisorbot is a command line program that can carry out various tasks to help a cryptocurrency investor analyse the data available on an exchange. \n\n" << std::endl;

	// Get the earliest time
	currentTime = orderBook.getEarliestTime();
	UserOption useroption{};

	// Start the useroption, which runs the advisorbot
	useroption.init();
	
	
	

}

// Step to move forward in timestamp, declared here to access orderbook directly.
void AdvisorMain::step() {
	std::cout << "Going to next time frame. " << std::endl;
	currentTime = orderBook.getNextTime(currentTime);
}

