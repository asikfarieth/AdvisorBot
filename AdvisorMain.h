#pragma once
#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"


extern OrderBook orderBook;

extern std::string currentTime;
class AdvisorMain
{
public:
	AdvisorMain();

	void init();

	
	void step();
	OrderBook orderBook{ "20200601.csv" };
	/*void help();*/
};