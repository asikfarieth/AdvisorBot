#include <iostream>
#include <algorithm>
#include "UserOption.h"
#include <string>
#include <vector>
#include <cctype>
#include "AdvisorMain.h"
#include "OrderBook.h"
#include "OrderBookEntry.h"


/* Intitalise constructor */

UserOption::UserOption() {


}

/* Init function to start the program */

void UserOption::init() {

	std::string input;

	/* While loop to run as long as the program is running. Grabs user input and parses it into vector of string and processes the commands */

	while (true) {
	   input = 	getUserCommand(); // runs the user command function
	  words = parseUserInput(input); // parses the command and stores into this variable
	  processUserCommand(words); // process the vector of string to call respective functions
	  std::cout << "\n\n" << std::endl; // additional space for aesthetics
	
	}


}
/* Gets the user input via getline function */

std::string UserOption::getUserCommand() {
	std::string userInput; // variable for user input
	std::cout << "Enter a command or type help for list of commands." << std::endl; // display 
	std::getline(std::cin, userInput); // grabs the line which the user has typed and stores it into userInput

	
	return userInput;

}

/* Command Parsing - Separates the command into various tokens of strings and returns a vector */

std::vector<std::string> UserOption::parseUserInput(std::string userInput) 
{
	
	char separator = ' '; // separator initialised here
	std::vector<std::string> words; // parsed commands stored as a vector
	signed int start, end; // start and end of the string 
	std::string word;
	start = userInput.find_first_not_of(separator, 0); // find the first character that is not the separator 

	do {
		end = userInput.find_first_of(separator, start); // sets the end to the last character
		if (start == userInput.length() || start == end) break; // breaks from the loop
		if (end >= 0) word = userInput.substr(start, end - start); // grabs the sub string
		else word = userInput.substr(start, userInput.length() - start); // grabts the sub string
		words.push_back(word); // stores the word into the array
		start = end + 1;
	} while (end > 0);

	
	return words;
}


// To process the vector of strings and to call respective functions

void UserOption::processUserCommand(std::vector<std::string> words) {

	// Transforms any upper case letters to lower case to accept any valid inputs
	std::transform(words[0].begin(), words[0].end(), words[0].begin(), ::tolower);

	if (words.size() == 1)
	{
		if (words[0] == "help")  // calls the help function 
		{
			help();
		}

		else if (words[0] == "time") // calls the time function
		{
			printCurrentTime();
		}

		else if (words[0] == "step") // calls the step function 
		{
			step();
		}

		else if (words[0] == "prod") { // calls the prod function
			prod();
		}

		else
		{
			std::cout << "Invalid command. Look below for the available commands or type: help <cmd> for details" << std::endl; // Validation: rejects other inputs and displays help
			help(); 
		}
	}



	else if (words.size() == 2)
	{
		std::transform(words[0].begin(), words[0].end(), words[0].begin(), ::tolower); // Converts uppercase strings into lower case
		std::transform(words[1].begin(), words[1].end(), words[1].begin(), ::tolower); // Converts uppercase strings into lower case

		if (words[0] == "help") // runs the help cmd function
		{
			helpCmd(words[1]);
		}
		else
		{
			std::cout << "Invalid command. Look below for the available commands or type: help <cmd> for details" << std::endl; // rejects other inputs and calls help
			help();
		}
	}


	else if (words.size() == 3)
	{
		std::transform(words[0].begin(), words[0].end(), words[0].begin(), ::tolower); // converts the uppercase strings into lower case
		std::transform(words[1].begin(), words[1].end(), words[1].begin(), ::toupper); // converts the product type string into upper case

		if (words[0] == "max") 
		{
			max(words[2], words[1]); //runs the max function
		}

		else if (words[0] == "min") 
		{
			min(words[2], words[1]); // runs the min function
		}

	}

	else if (words.size() == 4) 
	{
		//std::transform(words[0].begin(), words[0].end(), words[0].begin(), ::tolower); // converts the upper case strings into lower case
		//std::transform(words[1].begin(), words[1].end(), words[1].begin(), ::toupper); // converts the product type string into upper case
		//std::transform(words[2].begin(), words[2].end(), words[2].begin(), ::tolower); // converts the upper case strings into lower case
		
		if (words[0] == "avg")
		{
			average(words[1], words[2], words[3]); // calls the avg function
		}

		else if (words[0] == "trend")
		{
			trend(words[1], words[2], words[3]); // calls the trend function 
		}

		else if (words[0] == "predict")
		{
			double prediction = predict(words[1], words[2], words[3]); 
			std::cout << "The " << words[1] << " "<< words[3] <<" prediction is " << prediction << std::endl; // calls the prediction function and displays output
		}
	}

}

// Help function to display help commands
void UserOption::help() {

	std::cout << "Available list of commands: \n" << std::endl;
	std::cout << "1) help" << std::endl;
	std::cout << "2) help <cmd> - type a command in the place of <cmd>" << std::endl;
	std::cout << "3) prod" << std::endl;
	std::cout << "4) min" << std::endl;
	std::cout << "5) max" << std::endl;
	std::cout << "6) avg" << std::endl;
	std::cout << "7) predict" << std::endl;
	std::cout << "8) time" << std::endl;
	std::cout << "9) step" << std::endl;

}

// Help Command function to describe usage of each command 
void UserOption::helpCmd(std::string word)
{ 
	if (word == "prod") { // Display help for prod
		std::cout << "--------[help] prod--------" << std::endl;
		std::cout << "Description: list available products" << std::endl;
		std::cout << "Usage:" << std::endl;
		std::cout << "prod" << std::endl;

	}

	else if (word == "min") { // Display help for min
		std::cout << "--------[help] min--------" << std::endl;
		std::cout << "Description:  find minimum bid or ask for product in current time step" << std::endl;
		std::cout << "Usage:" << std::endl;
		std::cout << "min <product> <bid/ask>" << std::endl;
		std::cout << "Example:" << std::endl;
		std::cout << "min ETH/BTC ask" << std::endl;
	}

	else if (word == "max") { // Display help for max
		std::cout << "--------[help] max--------" << std::endl;
		std::cout << "Description:  find maximum bid or ask for product in current time step" << std::endl;
		std::cout << "Usage:" << std::endl;
		std::cout << "max <product> <bid/ask>" << std::endl;
		std::cout << "Example:" << std::endl;
		std::cout << "max ETH/BTC ask" << std::endl;

	}

	else if (word == "avg") { // Display help for avg
		std::cout << "--------[help] avg--------" << std::endl;
		std::cout << "Description:  compute average ask or bid for the sent product over the sent number of time steps." << std::endl;
		std::cout << "Usage:" << std::endl;
		std::cout << "avg product ask/bid timesteps" << std::endl;
		std::cout << "Example:" << std::endl;
		std::cout << "avg ETH/BTC ask 10" << std::endl;

	}

	else if (word == "predict") { // Display help for predict
		std::cout << "--------[help] predict--------" << std::endl;
		std::cout << "Description:  predict max or min ask or bid for the sent product for the next time step" << std::endl;
		std::cout << "Usage:" << std::endl;
		std::cout << "predict max/min product ask/bid" << std::endl;
		std::cout << "Example:" << std::endl;
		std::cout << "predict max ETH/BTC bid" << std::endl;

	}

	else if (word == "time") { // Display help for time
		std::cout << "--------[help] time--------" << std::endl;
		std::cout << "Description:   state current time in dataset, i.e. which timeframe are we looking at" << std::endl;
		std::cout << "Usage:" << std::endl;
		std::cout << "time" << std::endl;
		std::cout << "Example:" << std::endl;
		std::cout << "time" << std::endl;

	}


	else if (word == "step") { // Display help for step
		std::cout << "--------[help] step--------" << std::endl;
		std::cout << "Description:  move to next time step" << std::endl;
		std::cout << "Usage:" << std::endl;
		std::cout << "step" << std::endl;
		std::cout << "Example:" << std::endl;
		std::cout << "step" << std::endl;

	}

	else if (word == "trend") { // Display help for trend
		std::cout << "--------[help] trend--------" << std::endl;
		std::cout << "Description: Find the past few trends" << std::endl;
		std::cout << "Usage:" << std::endl;
		std::cout << "trend product ordertype timestep" << std::endl;
		std::cout << "Example:" << std::endl;
		std::cout << "trend ETH/BTC ask 10" << std::endl;

	}


	else
	{
		std::cout << "Invalid input. Available help commands: avg, predict, time, step, max, min, prod." << std::endl;
	}
	
}

// prints the current timestep
void UserOption::printCurrentTime() 
{

	std::cout << "Current time is: " << currentTime << std::endl;
}


// moves to the next timestep
void UserOption::step() 
{
	AdvisorMain stepObj;
	stepObj.step();
	std::cout << "Current time: " << currentTime << std::endl;
}


// calculates the max bid or ask for the product in current timestep
void UserOption::max(std::string ordertype, std::string product) 
{
	
	OrderBookType userOrder = OrderBookEntry::stringToOrderBookType(ordertype); // converts string to orderbook type
	std::vector<OrderBookEntry> entries = orderBook.getOrders(userOrder,
		product, currentTime); // grabs the entries

	std::cout << "Max " << ordertype << " of " << product << " for current timestamp: " << OrderBook::getHighPrice(entries) << std::endl;
}


// calculates the min bid or ask for the product in current timestep
void UserOption::min(std::string ordertype, std::string product) 
{

	OrderBookType userOrder = OrderBookEntry::stringToOrderBookType(ordertype); // converts string to orderbook type
	std::vector<OrderBookEntry> entries = orderBook.getOrders(userOrder,
		product, currentTime);

	std::cout << "Min " << ordertype << " of " << product << " for current timestamp: " << OrderBook::getLowPrice(entries) << std::endl;
}


// computes average ask or bid for the sent product over the sent number of timesteps
void UserOption::average(std::string prod, std::string orderTpe, std::string timesteps)
{
	int timestepsLoc = std::stoi(timesteps); // converts the timesteps into integer
	double avg = 0; // initialize average
	double total = 0; // initialize total
	int count = 0; // initial count to find the number of prices

	std::vector<std::string> times; // vector of string which stores the relevant timesteps
	OrderBookType orderTpeLoc; // To convert string to ordertype 

	orderTpeLoc = OrderBookEntry::stringToOrderBookType(orderTpe); // conversion to ordertype from string

	int index = grabCurrentIndex(); // grabs the current index of the timestamp (currenttime)
	int i = index; // stores the index into i

	// iterates through the various timestamps backwards for the given number of timesteps and stores them into the times array
	while (times.size() < timestepsLoc) {
		if (i < 1) {
			i = orders.size() - 1;
		}
		if (orders[i].timestamp != orders[i - 1].timestamp) { // to grab the previous timestamp, it compares the timestamps and only grabs the one which is different
			times.push_back(orders[i - 1].timestamp);
		}

		i = i - 1;
	}

	// iterates through all the orders and compares if the orders are of relevant type according to the inputs received
	for (int j = 0; j < orders.size() - 1; j++) 
	{
		for (int k = 0; k < times.size(); k++) 
		{
			if ((orders[j].timestamp == times[k]) && (orders[j].product == prod) && (orders[j].orderType == orderTpeLoc)) 
			{
				count = count + 1;
				total = total + orders[j].price; // computes total of relevant orders 
		
			}
		}
	}

	avg = total / count; // computers the average
	std::cout << "Average: " << avg << std::endl; // outputs the average
	

	
}
// grabs the current index for the current time stamp
int UserOption::grabCurrentIndex() {
	for (int i = 0; i < orders.size() - 1; i++) { // iterate through the orders

		if (orders[i].timestamp == currentTime) { // returns the index of the current timestamp
			return i;
		}
	}

}



// Extention: Own command. 
void UserOption::trend(std::string prod, std::string orderTpe, std::string timesteps)
{
	int timestepsLoc = std::stoi(timesteps); // grabs the timesteps and converts it into integer
	double avg = 0; // initializes average 
	double total = 0; // initializes total
	int count = 0; // intializes count 
	int up = 0; // initialize up trend
	int down = 0; //initialize down trend
	std::vector<std::string> times; // vector of timestamps
	OrderBookType orderTpeLoc; // convert string to ordertype
	std::vector <double> aveList; // list 

	orderTpeLoc = OrderBookEntry::stringToOrderBookType(orderTpe); // convert string to order type

	int index = grabCurrentIndex(); // grabs the current index of curren timestamp
	int i = index; // stores the index into i
	while (times.size() < timestepsLoc) { // iterate the relevant timestamps
		if (i < 1) { // checks if ordersize 
			i = orders.size() - 1; 
		}
		if (orders[i].timestamp != orders[i - 1].timestamp) {
			times.push_back(orders[i - 1].timestamp);
		}

		i = i - 1;
	}
	for (int k = 0; k < times.size(); k++)
	{
		count = 0; // resets count 
		total = 0; // resets total
		avg = 0; // resets average
		for (int j = 0; j < orders.size() - 2; j++) // iterate through the orders
		{
			if ((orders[j].timestamp == times[k]) && (orders[j].product == prod) && (orders[j].orderType == orderTpeLoc))
			{
				total = total + orders[j].price; // compute the total for all the orders
				count = count + 1;
			}
		}
		avg = total / count;
		aveList.push_back(avg); // store the averages into the vector
	}
	 
	for (int l = 0; l < aveList.size(); l++) { // iterates through the list of averages
		if (aveList[l] > aveList[l+1]) {
			up = up + 1; // increment up if the average is increased
		}
		if (aveList[l] <= aveList[l+1]) {
			down = down + 1; // increment up if the average is decreased
		}
	}



	std::cout << "Up trend: " << up << std::endl; // list up trends 
	std::cout << "Down trend: " << down << std::endl; // list down trends


}

// Lists all the product types via the getKnownProducts function
void UserOption::prod()
{
	std::cout << "Product List:" << std::endl;
	for (std::string const& p : orderBook.getKnownProducts())
	{
		std::cout << p << std::endl;
	}
}


/* Predict function: Grabs the max/min via type, products via prod and ask or bid via orderTpe */

double UserOption::predict(std::string type, std::string prod, std::string orderTpe)
{
	// prediction for past 10 time steps
	std::string timesteps = "10";

	// converts the string of timesteps into integer
	int timestepsLoc = std::stoi(timesteps);

	// initilize average
	double avg = 0;

	// initial total of all prices
	double total = 0;

	// count of number of timestamps
	int count = 0;

	// store the number of up trends
	int up = 0;

	// store the number of down trends
	int down = 0;

	// initalizes the vector "times" which will be used to store the relevant timesteps
	std::vector<std::string> times;

	// To convert the order type string into ordertype
	OrderBookType orderTpeLoc;

	// vector of all relevant averages of prices
	std::vector <double> aveList;

	// convert the order type string to ordertype 
	orderTpeLoc = OrderBookEntry::stringToOrderBookType(orderTpe);

	// grabs the current index of the timestamp (currentTime)
	int index = grabCurrentIndex();

	// stores the index into i
	int i = index;

	// iterates through the various timestamps backwards for the given number of timesteps and stores them into the times array
	while (times.size() < timestepsLoc) {
		if (i < 1) {
			i = orders.size() - 1;
		}
		if (orders[i].timestamp != orders[i - 1].timestamp) { // to grab the previous timestamp, it compares the timestamps and only grabs the one which is different
			times.push_back(orders[i - 1].timestamp);
		}

		i = i - 1;
	}


	// iterates through the vector of timesteps 
	for (int k = 0; k < times.size(); k++)
	{
		count = 0;
		total = 0;
		avg = 0;
		for (int j = 0; j < orders.size() - 2; j++)
		{
			if ((orders[j].timestamp == times[k]) && (orders[j].product == prod) && (orders[j].orderType == orderTpeLoc))
			{
				total = total + orders[j].price;
				count = count + 1;
			}
		}
		avg = total / count;

		aveList.push_back(avg);
	}

	// counts the number of times the trend is upwards
	int countMax = 0;

	// counts the number of times the trend is downwards
	int countMin = 0;

	// finds the total of all the timesteps where the the trend was upwards

	double maxDiffTotal = 0;

	// finds the total of all the timesteps where the the trend was downwards
	double minDiffTotal = 0;

	// iterates through the list of averages and finds the total of increased and decreased trend timesteps
	for (int l = 0; l < aveList.size(); l++) {
		if (aveList[l] > aveList[l + 1]) {
			countMax = countMax + 1;
			maxDiffTotal = aveList[l] - aveList[l + 1];
		}
		if (aveList[l] <= aveList[l + 1]) {
			countMin = countMin + 1;
			minDiffTotal = aveList[l + 1] - aveList[l];
		}
	}

	// averages of timesteps where there were upward trend, and average of timesteps where therewere downward trend
	double maxAve = maxDiffTotal / countMax;
	double minAve = minDiffTotal / countMin;

	
	// finds the total average of all timesteps for the current product and order type
	double totalAve = 0;
	int totalAveCount = 0;
	for (int e = 0; e < aveList.size(); e++) {
		totalAve = totalAve + aveList[e];
		totalAveCount = totalAveCount + 1;
	}

	// adds an average of increase to the max predict and subtracts an average of decrease from min predict
	double max_predict = totalAve / totalAveCount + maxAve;
	double min_predict = totalAve / totalAveCount - minAve;

	//std::cout << "max" << max_predict << std::endl;
	if (type == "max") {
		return max_predict;
	}
	else if (type == "min"){
		return min_predict;
	}
}