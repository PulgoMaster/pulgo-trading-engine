#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include "EnumClass.h"
using namespace std;

class Orderbook
{
public:
    string dateTime;

    CoinType product;

    BidAsk bidAsk;

    double coinAmmount;

    double buyCost;
    
    Orderbook() = default;

    Orderbook(string dateTime,
              CoinType product,
              BidAsk bidAsk,
              double coinAmmount,
              double buyCost);

    vector<Orderbook> LoadOrderBook(vector<string> combined, vector <Orderbook> empty);
    
    std::string getEarliestTime();
};
