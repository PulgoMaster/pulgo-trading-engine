# PulgoMaster — C++ Crypto Trading Engine

Real-time limit-order-book simulator built from raw Binance CSV data.

**Features**
- Full order-book parsing (timestamp, product, bid/ask, amount, price)
- Interactive console menu (wallet, place bids/asks, stats)
- Highest / lowest / average price per coin pair
- Date + coin + bid/ask filtering
- 100 % standard C++17 — no external libraries

**Run**
```bash
g++ -std=c++17 *.cpp -o PulgoMaster
./PulgoMaster
