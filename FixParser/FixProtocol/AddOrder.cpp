#include "AddOrder.h"

void AddOrder::addOrder(const std::string clOrdID, const std::string price, const std::string qty, std::string Sender, std::string Target) {
        auto currentTime = std::chrono::system_clock::now();
        std::time_t currentTime_t = std::chrono::system_clock::to_time_t(currentTime);
        std::string orderData;
        //std::vector<std::pair<std::string, std::string>> orderData;
        orderData.append("11=" ); // sender ID
        orderData.append(clOrdID);
        orderData.append("^21=3"); // 3 = Manual // 1 = Automated
        orderData.append("^55=TECK"); // nos special symbol
        orderData.append("^54=1" );//  1 = Buy, 2 = Sell, //side
        orderData.append("^60=" );
        orderData.append(GetTime());
        orderData.append("^40=2" ); //ordType: 1 = Market, 2 = Limit, 3 = Stop, 4 = Stop limit, ...
        orderData.append("^44=" ); // price
        orderData.append(price);
        orderData.append("^38=" ); // qty
        orderData.append(qty);
        orderData.append("^");
        AddHeader header;
        Trailler trailler;
        orderData.insert(0, header.HeaderMaker(orderData, "D", "1", Sender, Target));
        orderData.append(trailler.TraillerMaker(orderData));
        std::cout << "Order Data:\n" << orderData << std::endl;
    }