# PulgoMaster — C++ Crypto Trading Engine

A full limit-order-book trading simulator built from real Binance CSV data.

### Features
- Real-time order book parsing (timestamp, product, bid/ask, amount, price)
- Interactive console menu
- Wallet simulation (1000 USDT start)
- Place bids/asks
- Stats: highest/lowest/average price per coin pair
- Date + coin + bid/ask filtering
- 100 % standard C++17 — no external libraries

### Tech Stack
- C++17
- STL only

### How to Run
```bash
g++ -std=c++17 *.cpp -o PulgoMaster.exe
./PulgoMaster.exe
