
#include "OrderBookEntry.h"
#include "EnumClass.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;


static string fixTrailingDot(string s) {
    if (!s.empty() && s.back() == '.') s += '0';
    return s;
}


static CoinType stringToCoinType(const string& s) {
    if (s == "DOGE/BTC") return CoinType::DOGEBTC;
    if (s == "ETH/BTC") return CoinType::ETHBTC;
    if (s == "BTC/USDT") return CoinType::BTCUSDT;
    if (s == "ETH/USDT") return CoinType::ETHUSDT;
    if (s == "DOGE/USDT") return CoinType::DOGEUSDT;
    return CoinType::error;
}

static BidAsk stringToBidAsk(const string& s) {
    if (s == "bid") return BidAsk::bid;
    if (s == "ask") return BidAsk::ask;
    return BidAsk::error;
}


Orderbook::Orderbook(string dt, CoinType p, BidAsk ba, double ca, double bc)
    : dateTime(std::move(dt)), product(p), bidAsk(ba), coinAmmount(ca), buyCost(bc) {}

vector<Orderbook> Orderbook::LoadOrderBook(vector<string> combined, vector<Orderbook> empty) {
    ifstream file("dataset.csv");
    if (!file.is_open()) {
        cerr << "Error opening dataset.csv\n";
        return empty;
    }

    string line;
    while (getline(file, line)) {
        combined.push_back(line);
    }

    vector<Orderbook> orders;
    for (const string& line : combined) {
        stringstream ss(line);
        string dt, prod, ba, amt, price;

        getline(ss, dt, ',');
        getline(ss, prod, ',');
        getline(ss, ba, ',');
        getline(ss, amt, ',');
        getline(ss, price, ',');

        amt = fixTrailingDot(amt);
        price = fixTrailingDot(price);

        CoinType p = stringToCoinType(prod);
        BidAsk b = stringToBidAsk(ba);
        if (p == CoinType::error || b == BidAsk::error) continue;

        double amount = stod(amt);
        double cost = stod(price);

        orders.emplace_back(dt, p, b, amount, cost);
    }
    return orders;
}


string Orderbook::getEarliestTime() {
    extern vector<Orderbook> orderBookList;  
    if (orderBookList.empty()) return "";
    string earliest = orderBookList[0].dateTime;
    for (const auto& o : orderBookList) {
        if (o.dateTime < earliest) earliest = o.dateTime;
    }
    return earliest;
}