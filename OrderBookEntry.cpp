#include "PulgoMaster.h"
#include "OrderBookEntry.h"
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>

vector<Orderbook> orderBookEntry;
int LineQuantity = 0;
CoinType checkType(string temp)

{
    if (temp == "DOGE/BTC")
    {
        return {CoinType::DOGEBTC};
    }
    else if (temp == "ETH/BTC")
    {
        return {CoinType::ETHBTC};
    }
    else if (temp == "BTC/USDT")
    {
        return {CoinType::BTCUSDT};
    }
    else if (temp == "ETH/USDT")
    {
        return {CoinType::ETHUSDT};
    }
    else if (temp == "DOGE/USDT")
    {
        return {CoinType::DOGEUSDT};
    }
    else
    {
        return {CoinType::error};
    }
}

BidAsk checkBidAsk(string temp)
{
    if (temp == "bid")
    {
        return {BidAsk::bid};
    }
    else if (temp == "ask")
    {
        return {BidAsk::ask};
    }
    else
    {
        return {BidAsk::error};
    }
}

vector<Orderbook> Orderbook::LoadOrderBook(vector<string> combined, vector<Orderbook> empty)
{

    ifstream archivo("dataset.csv");
    if (!archivo.is_open())
    {
        cerr << "Error al abrir el archivo." << endl;
        return empty;
    }

    int lineas = 0;
    string linea = "";
    while (getline(archivo, linea))
    {
        combined.push_back(linea);
        lineas++;
    }

    LineQuantity = lineas;

    for (string strung : combined)
    {
        string temp = "";
        Orderbook tempo;
        CoinType tempCoin;
        BidAsk tempBidAsk;
        int lorge = strung.length();
        int tnuoc = 0;
        double tempNumb = 0;

        for (char c : strung)
        {

            if (c == ',')
            {
                switch (tnuoc)
                {
                case 0:
                    tempo.dateTime = temp;
                    break;
                case 1:
                    tempCoin = checkType(temp);
                    tempo.product = tempCoin;
                    break;
                case 2:
                    tempBidAsk = checkBidAsk(temp);
                    tempo.bidAsk = tempBidAsk;
                    break;
                case 3:
                    tempNumb = std::stod(temp);
                    tempo.coinAmmount = tempNumb;
                    break;
                }

                temp = "";
                tnuoc++;
            }
            else
            {
                temp += c;
            }
        }
        if (tnuoc == 4)
        {
            tempNumb = std::stod(temp);
            tempo.buyCost = tempNumb;
        }
        orderBookEntry.push_back(tempo);
    }
    return orderBookEntry;
    
}

std::string Orderbook::getEarliestTime()
{
    return orderBookEntry[0].dateTime;
}