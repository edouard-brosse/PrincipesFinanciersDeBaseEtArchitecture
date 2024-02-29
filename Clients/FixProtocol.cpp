#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <unordered_map>
#include <sstream>
#include "FixProtocol.h"

std::string LibData::GetTime() {
    std::time_t currentTime = std::time(nullptr);
    std::tm* now = std::localtime(&currentTime);
    std::stringstream ss;
    ss << std::put_time(now, "%y%m%d-%H:%M:%S");
    return ss.str();
}

std::string AddHeader::HeaderMaker(std::string body, std::string MsgType, std::string RqtNbn, std::string Sender, std::string Target) {
    std::string header = "";
    header.append("8=FIX.4.2^");
    header.append("9=" );
    header.append(std::to_string(body.length()));
    header.append("^35=" );
    header.append(MsgType);
    header.append("^49=");
    header.append(Sender); 
    header.append("^56=");
    header.append(Target);
    header.append("^34="  );
    header.append(RqtNbn);
    header.append("^52=");
    header.append(GetTime());
    header.append("^");
    return header;
}

std::string Trailler::traillerCalculated(std::string body) {
    int sum = 0;
    for (char c : body) {
        sum += c;
    }
    return std::to_string(sum % 256);
}

std::string Trailler::TraillerMaker(std::string body) {
    std::string trailler = "";
    trailler.append("10=" );
    trailler.append(traillerCalculated(body));
    return trailler;
}

std::string AddOrder::addOrder(const std::string price, const std::string qty, std::string Sender, std::string Target) {
    std::string orderData;
    orderData.append("11=" );
    orderData.append(std::to_string(++clOrdID));
    orderData.append("^21=3");
    orderData.append("^55=TECK");
    orderData.append("^54=1" );
    orderData.append("^60=" );
    orderData.append(GetTime());
    orderData.append("^40=2" );
    orderData.append("^44=" );
    orderData.append(price);
    orderData.append("^38=" );
    orderData.append(qty);
    orderData.append("^");
    AddHeader header;
    Trailler trailler;
    orderData.insert(0, header.HeaderMaker(orderData, "D", "1", Sender, Target));
    orderData.append(trailler.TraillerMaker(orderData));
    return orderData;
}

std::string AddOrderSell::SellOrder(const std::string price, const std::string qty, std::string Sender, std::string Target) {
    std::string orderData;
    orderData.append("11=" );
    orderData.append(std::to_string(++clOrdID));
    orderData.append("^21=3");
    orderData.append("^55=TECK");
    orderData.append("^54=1" );
    orderData.append("^60=" );
    orderData.append(GetTime());
    orderData.append("^40=2" );
    orderData.append("^44=" );
    orderData.append(price);
    orderData.append("^38=" );
    orderData.append(qty);
    orderData.append("^");
    AddHeader header;
    Trailler trailler;
    orderData.insert(0, header.HeaderMaker(orderData, "D", "1", Sender, Target));
    orderData.append(trailler.TraillerMaker(orderData));
    return orderData;
}

std::string UpdateOrder::UpdateOrd(const std::string clOrdID, std::string price,  std::string qty, std::string Sender, std::string Target, std::string OrderId, std::string NewID, std::string OrderType) {            
    std::string orderData;
    orderData.append("11=" );
    orderData.append(clOrdID);
    orderData.append("^41=" );
    orderData.append(NewID);
    orderData.append("^21=3");
    orderData.append("^55=TECK");
    orderData.append("^54=" );
    orderData.append(OrderType);
    orderData.append("^60=" );
    orderData.append(GetTime());
    orderData.append("^40=" );
    orderData.append( OrderType);
    orderData.append("^37=" );
    orderData.append(OrderId);
    orderData.append("^44=" );
    orderData.append(price);
    orderData.append("^38=" );
    orderData.append(qty);
    orderData.append("^");
    orderData.insert(0, HeaderMaker(orderData, "G", "1", Sender, Target));
    orderData.append(TraillerMaker(orderData));
    return orderData;
}

std::string OrderCancel::CancelOrd(const std::string clOrdID, std::string Sender, std::string Target, std::string OrderId, std::string OrderType) {            
    std::string orderData;
    orderData.append("^11=" );
    orderData.append(clOrdID);
    orderData.append("^41=" );
    orderData.append(OrderId);
    orderData.append("^21=3");
    orderData.append("^55=TECK");
    orderData.append("^54=" );
    orderData.append(OrderType);
    orderData.append("^60=" );
    orderData.append(GetTime());
    orderData.append("^40=2" );
    orderData.append("^");
    orderData.insert(0, HeaderMaker(orderData, "F", "1", Sender, Target));
    orderData.append(TraillerMaker(orderData));
    return orderData;
}

std::string ExReport::ExecutionReport( std::string Sender, std::string Target, std::string OrderType, std::string ExecType, std::string OrdStatus, std::string nb, std::string prixMoyen, std::string ExID) {            
    std::string orderData;
    orderData.append("^37=8" );
    orderData.append("^17=");
    orderData.append(ExID);
    orderData.append("^55=TECK");
    orderData.append("^54=" );
    orderData.append(OrderType);
    orderData.append("^150=" );
    orderData.append(ExecType);
    orderData.append("^39=" );
    orderData.append(OrdStatus);
    orderData.append("^151=" );
    orderData.append("^14=");
    orderData.append(nb);
    orderData.append("^6=");
    orderData.append(prixMoyen);
    orderData.append("^");
    orderData.insert(0, HeaderMaker(orderData, "8", "1", Sender, Target));
    orderData.append(TraillerMaker(orderData));
    return orderData;
}

std::string LogOn::logOn( std::string Sender, std::string Target) {            
    std::string orderData;
    orderData.append("^98=0");
    orderData.append("^108=30");
    orderData.insert(0, HeaderMaker(orderData, "A", "1", Sender, Target));
    orderData.append(TraillerMaker(orderData));
    return orderData;
}

//class MarketSnapshot: public AddHeader, public Trailer{
//    public:
//        void MarketDataSnapshot( std::string Sender, std::string Target, std::string OrderType, std::string ExecType, std::string OrdStatus, std::string nb, std::string prixMoyen, sdtd::string ExID) {            
//            std::string orderData;
//            orderData.append("^37=8" );
//            orderData.append("^17="); ///////////////////// completer 
//            orderData.append(ExID)
//            orderData.append("^55=TECK"); // nos special symbol
//            orderData.append("^54=" );//  1 = Buy, 2 = Sell, //side
//            orderData.append(OrderType);
//            orderData.append("^150=" );
//            orderData.append(ExecType);
//            orderData.append("^39=" );
//            orderData.append(OrdStatus);
//            orderData.append("^151=" ); //////// check this file
//            orderData.append("^14=");// nombre d'achat/vente executé
//            orderData.append(nb);
//            orderData.append("^6="); // prix moyen pour toute les vente de l'ordre
//            orderData.append(prixMoyen);
//            orderData.append("^");
//            orderData.insert(0, HeaderMaker(orderData, "8", "1", Sender, Target));
//            orderData.append(TraillerMaker(orderData));
//            std::cout << "EXECUTION REPORT Data:\n" << orderData << std::endl;
//        }
//};




// int main(){
//     AddOrder addOrder;
//     std::string clOrdID = "1";
//     std::string price = "100";
//     std::string qty = "10";
//     addOrder.addOrder(price, qty, "SENDER", "TARGET");
//     UpdateOrder updateOrder;
//     //updateOrder.UpdateOrd(clOrdID, price, qty, "SENDER", "TARGET", "10", "2");
//     updateOrder.UpdateOrd(clOrdID, price,  qty,  "Sender", "Target", "10", "NewID", "2");
//     OrderCancel orderCancel;
//     orderCancel.CancelOrd(clOrdID, "Sender", "Target", "10", "2");
//     ExReport exReport;
//     exReport.ExecutionReport("Sender", "Target", "10", "2", "0", "0", "10", "13");
//     LogOn logOn;
//     logOn.logOn("Sender", "Target");
// }
