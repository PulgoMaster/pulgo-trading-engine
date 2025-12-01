#pragma once
#include "OrderBookEntry.h"
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

class PulgoMaster
{
public:
    PulgoMaster() = default;
    /** Call this to start the sim */
    void init();
    vector<Orderbook> orderBookEntry;

private:
    string currentTime;
    void printMenu();
    void printHelp();
    void filterBA();
    void filterCT(int ammountLines);
    void HighestCoin();
    void LowestCoin();
    void averageCoin();
    void menuHelp();
    void showStats();
    void continueMenu();
    void leaveMenu();
    void wrongAnswer();
    void showWallet();
    void dateFilter();
    int chooseMenu();
    CoinType checkType(string temp);
    BidAsk checkBidAsk(string temp);
    int UserAsk();
    int UserBid();
    void processUserOption(int userOption);
    vector<Orderbook> orders;
    
};