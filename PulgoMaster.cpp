#include "OrderBookEntry.h"
#include "EnumClass.h"
#include "PulgoMaster.h"
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

Orderbook order;

int userinput = 0;
int ask = 0;
int bid = 0;
int wallet = 1000;

vector<string> combined;
vector<Orderbook> orderBookList;
vector<string> dateTime;
vector<string> product;
vector<string> bidAsk;
vector<string> coinAmmount;
vector<string> buyCost;
vector<Orderbook> empty;
Orderbook early;

string linea;

vector<Orderbook> filterBidAsk;
vector<Orderbook> filterCoinType;

int filterCoinSize;
int filterBidAskSize;

int ammountLines = 0;

 std::string toStringProduct(CoinType type)
{
    switch (type)
    {
    case CoinType::DOGEBTC:
        return "DOGEBTC";
    case CoinType::ETHBTC:
        return "ETHBTC";
    case CoinType::BTCUSDT:
        return "BTCUSDT";
    case CoinType::ETHUSDT:
        return "ETHUSDT";
    case CoinType::DOGEUSDT:
        return "DOGEUSDT";
    default:
        return "Unknown";
    }
};
std::string toString(BidAsk type)
{
    switch (type)
    {
    case BidAsk::bid:
        return "Bid";
    case BidAsk::ask:
        return "Ask";
    default:
        return "Unknown";
    }
}

void PulgoMaster::filterCT(int ammountLines)
{
    cout << filterCoinSize << endl;
    Orderbook temporaryCT;
    vector<Orderbook> temp2;
    int typeCoin;
    bool first = true;
    do
    {
        if (first == true)
        {
            cout << "What coin do you want to check?" << endl;
            cout << "0: DOGE/BTC" << endl;
            cout << "1: ETH/BTC" << endl;
            cout << "2: BTC/USDT" << endl;
            cout << "3: ETH/USDT" << endl;
            cout << "4: DOGE/USDT" << endl;
            cin >> typeCoin;
        }
        else
        {
            cout << "Wrong option, try 0-4." << endl;
            cout << "What coin do you want to check?" << endl;
            cout << "0: DOGE/BTC" << endl;
            cout << "1: ETH/BTC" << endl;
            cout << "2: BTC/USDT" << endl;
            cout << "3: ETH/USDT" << endl;
            cout << "4: DOGE/USDT" << endl;
            cin >> typeCoin;
        }
        first == false;
    } while (typeCoin > 4);

    for (int i = 0; i < ammountLines; i++)
    {
        bool enterCoinType = false;
        if (typeCoin == 0 && orderBookList.at(i).product == CoinType::DOGEBTC)
        {
            temporaryCT = orderBookList.at(i);
            enterCoinType = true;
        }
        else if (typeCoin == 1 && orderBookList.at(i).product == CoinType::ETHBTC)
        {
            temporaryCT = orderBookList.at(i);
            enterCoinType = true;
        }
        else if (typeCoin == 2 && orderBookList.at(i).product == CoinType::BTCUSDT)
        {
            temporaryCT = orderBookList.at(i);
            enterCoinType = true;
        }
        else if (typeCoin == 3 && orderBookList.at(i).product == CoinType::ETHUSDT)
        {
            temporaryCT = orderBookList.at(i);
            enterCoinType = true;
        }
        else if (typeCoin == 4 && orderBookList.at(i).product == CoinType::DOGEUSDT)
        {
            temporaryCT = orderBookList.at(i);
            enterCoinType = true;
        }
        if (enterCoinType == true)
        {
            temp2.push_back(temporaryCT);
            enterCoinType = false;
        }
    }
    filterCoinType = temp2;
    filterCoinSize = filterCoinType.size();
}

void PulgoMaster::filterBA()
{
    Orderbook temporaryBA;
    string convert = "";
    vector<Orderbook> temp3;
    int typeBidAsk;
    bool first = true;
    do
    {
        if (first == true)
        {
            cout << "Do you want to check Bid or Ask?" << endl;
            cout << "0: Bid" << endl;
            cout << "1: Ask" << endl;
            cin >> typeBidAsk;
        }
        else
        {
            cout << "Wrong option, try 0-1." << endl;
            cout << "Do you want to check Bid or Ask?" << endl;
            cout << "0: Bid" << endl;
            cout << "1: Ask" << endl;
            cin >> typeBidAsk;
        }
        first == false;

    } while (typeBidAsk > 1);

    for (int i = 0; i < filterCoinSize; i++)
    {
        bool enterBidAsk = false;
        if (typeBidAsk == 0 && orderBookList.at(i).bidAsk == BidAsk::bid)
        {
            temporaryBA = orderBookList.at(i);
            enterBidAsk = true;
        }
        else if (typeBidAsk == 1 && orderBookList.at(i).bidAsk == BidAsk::ask)
        {
            temporaryBA = orderBookList.at(i);
            enterBidAsk = true;
        }
        if (enterBidAsk == true)
        {
            temp3.push_back(temporaryBA);
            enterBidAsk = false;
        }
    }
    filterBidAsk = temp3;
    filterBidAskSize = filterBidAsk.size();
}

void PulgoMaster::HighestCoin()
{

    Orderbook change;
    for (int i = 0; i < filterBidAskSize; i++)
    {

        for (int j = i + 1; j < filterBidAskSize - 1; j++)
        {

            if (filterBidAsk.at(j).coinAmmount > filterBidAsk.at(i).coinAmmount)
            {
                change = filterBidAsk.at(i);
                filterBidAsk.at(i).coinAmmount = filterBidAsk.at(j).coinAmmount;
                filterBidAsk.at(j).coinAmmount = change.coinAmmount;
            }
        }
    }
    cout << "The highest cost is: " << filterBidAsk.at(0).dateTime << " " << "$" << fixed << setprecision(8) << filterBidAsk.at(0).coinAmmount << endl;
}

void PulgoMaster::LowestCoin()
{

    Orderbook change;
    for (int i = 0; i < filterBidAskSize; i++)
    {

        for (int j = i + 1; j < filterBidAskSize - 1; j++)
        {

            if (filterBidAsk.at(j).coinAmmount > filterBidAsk.at(i).coinAmmount)
            {
                change = filterBidAsk.at(i);
                filterBidAsk.at(i).coinAmmount = filterBidAsk.at(j).coinAmmount;
                filterBidAsk.at(j).coinAmmount = change.coinAmmount;
            }
        }
    }

    cout << "The lowest cost is " << filterBidAsk.at(filterBidAskSize - 1).dateTime << " " << "$"<< fixed << setprecision(10) << filterBidAsk.at(filterBidAskSize - 1).coinAmmount << endl;
}

void PulgoMaster::averageCoin()
{
    double sum;
    for (int i = 0; i < filterBidAskSize; i++)
    {
        sum += filterBidAsk.at(i).coinAmmount;
    }
    sum = sum / filterBidAskSize;
    cout << "The average cost is " << sum << endl;
}

void PulgoMaster::menuHelp()
{
    std::cout << "Help - choose options from the menu" << std::endl;
    std::cout << "and follow the on screen instructions." << std::endl;
}

void PulgoMaster::showStats()
{
    int optionzz = 5;
    filterCT(ammountLines);

    filterBA();
    do
    {
        cout << "Do you want to check for Average, Highest, or Lowest?" << endl;
        cout << "0: Highest" << endl;
        cout << "1: Lowest" << endl;
        cout << "2: Average" << endl;
        cin >> optionzz;
    
        switch (optionzz)
        {

        case 0:
            HighestCoin();
            break;
        case 1:
            LowestCoin();
            break;
        case 2:
            averageCoin();
            break;
        default:
            cout << "Wrong option, try 0-2." << endl;
        }
    } while (optionzz > 2);
}

int PulgoMaster::UserAsk()
{
    std::cout << "How much is your ask?" << std::endl;
    cin >> ask;
    cout << "your ask is: " << ask << endl;
    return ask;
}

int PulgoMaster::UserBid()
{
    std::cout << "How much is your bid?" << std::endl;
    cin >> bid;
    cout << "your bid is: " << bid << endl;
    return bid;
}

void PulgoMaster::showWallet()
{
    std::cout << "Your wallet has: " << wallet << std::endl;
}

void PulgoMaster::continueMenu()
{
    std::cout << "Continue to menu again" << std::endl;
}

void PulgoMaster::dateFilter(){
    int dateOption = 0;
    do{
    cout << "Filter by oldest or earliest date" << endl;
    cout << "0: Oldest" << endl << "1: Earliest" << endl;
    cin >> dateOption; 
    
        switch(dateOption){
            case 0:
                early = orderBookList.at(0);
                for (int i = 0; i < ammountLines; i++)
                {
                    if (early.dateTime <= orderBookList.at(i).dateTime){
                        early = orderBookList.at(i);
                    }
                }
                cout << "The oldest Entry is: " << early.dateTime << " " << toString(early.bidAsk) << " " << toStringProduct(early.product) << " " << "Buy cost is: " << early.buyCost << " "<< "Coin ammount is: " << early.coinAmmount << endl;
                break;
            case 1:
                early = orderBookList.at(0);
                
                for (int i = 0; i < ammountLines; i++)
                {
                    if (early.dateTime > orderBookList.at(i).dateTime)
                    {
                        //fix here not work date time on early
                        std::cout << "DEBUG: early.dateTime = " << early.dateTime << std::endl;
                        early = orderBookList.at(i);
                        
                    }
                }
                cout << "The earliest Entry is: " << early.dateTime << " " << toString(early.bidAsk) << " " << toStringProduct(early.product) << " " << "Buy cost is: " << early.buyCost << " " << "Coin ammount is: " << early.coinAmmount << endl;
                break;

            default:
                cout << "weird error if you got here" << endl;
                break;
            }
    } while (dateOption > 1);
}

void PulgoMaster::leaveMenu()
{
    std::cout << "You chose to exit" << std::endl;
    std::cout << "Goodbye" << std::endl;
}

void PulgoMaster::wrongAnswer()
{
    std::cout << "Enter a proper option between 1-8" << std::endl;
}


int PulgoMaster::chooseMenu()
{
    cout << endl;
    std::cout << "Menu Options" << std::endl;
    std::cout << "=========================" << std::endl;
    std::cout << "1: Print Help" << std::endl;
    std::cout << "2: Print Exchange Stats" << std::endl;
    std::cout << "3: Place an ask" << std::endl;
    std::cout << "4: Place a bid" << std::endl;
    std::cout << "5: Print Wallet" << std::endl;
    std::cout << "6: Continue" << std::endl;
    std::cout << "7: Filter Dates" << endl;
    std::cout << "8: Leave Menu" << std::endl;
    std::cout << "=========================" << std::endl;
    cin >> userinput;
    cout << endl;
    return userinput;
}



void PulgoMaster::init()
    {
        
        orderBookList = order.LoadOrderBook(combined, empty);
        currentTime = order.getEarliestTime();
        ammountLines = orderBookList.size();

        chooseMenu();
        do

        {
            switch (userinput)
            {

            case 1:
                menuHelp();
                break;

            case 2:
                showStats();
                break;

            case 3:
                UserAsk();
                break;

            case 4:
                UserBid();
                break;

            case 5:
                showWallet();
                break;

            case 6:
                continueMenu();
                break;
            case 7:
                dateFilter();
                break;

            case 8:
                leaveMenu();
                break;

            default:
                wrongAnswer();
            }
            chooseMenu();
        } while (userinput != 8);
    }
