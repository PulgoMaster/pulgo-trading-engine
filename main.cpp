#include "PulgoMaster.h"
#include <iostream>

int main() {
    PulgoMaster app;
    app.init();

    std::cout << "\n\nPress ENTER to exit...";
    std::cin.get();
    return 0;
}