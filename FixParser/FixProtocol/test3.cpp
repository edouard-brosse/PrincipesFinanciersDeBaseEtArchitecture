#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <unordered_map>
#include "AddOrder.h"




int main(int a, char** av){
    AddOrder addOrder;
    std::string clOrdID = "1";
    std::string price = "100";
    std::string qty = "10";
    addOrder.addOrder(clOrdID, price, qty, "SENDER", "TARGET");
}
