#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <unordered_map>

class LibData {
private:

public:
    std::string GetTime() {
        std::time_t currentTime = std::time(nullptr);
        std::tm* now = std::localtime(&currentTime);
        std::stringstream ss;
        ss << std::put_time(now, "%y%m%d-%H:%M:%S");

        std::string dateTimeStr = ss.str();

        return dateTimeStr;
    }
};

class AddHeader: public LibData{
public:
    std::string HeaderMaker(std::string body, std::string MsgType, std::string RqtNbn, std::string Sender, std::string Target) {
        std::string header = "";
        std::time_t t = std::time(nullptr);
        std::tm* now = std::localtime(&t);

        header.append("8=FIX.4.2^");
        header.append("9=" );
        header.append(std::to_string(body.length()));
        header.append("^35=" );
        header.append(MsgType);
        header.append("^49="); // You need to specify sender and target comp ids
        header.append(Sender); 
        header.append("^56="); // Or adjust accordingly
        header.append(Target);
        header.append("^34="  );
        header.append(RqtNbn);
        //header.append("^52=" + std::to_string(now->tm_hour) + ":" + std::to_string(now->tm_min) + ":" + std::to_string(now->tm_sec) + "^");
        header.append("^52=");
        header.append(GetTime());
        header.append("^");
        return header;
    }
};

class Trailler {
private:
    std::string traillerCalculated(std::string body);
public:
    std::string TraillerMaker(std::string body);
};

std::string Trailler::traillerCalculated(std::string body) {
    std::string trailler = "";
    int sum = 0;
    for (char c : body) {
        sum += c; // Ajoute la valeur ASCII de chaque caractère
    }
    int temp = sum % 256;
    trailler = std::to_string(temp); // Retourne le résultat modulo 256
    return trailler;
}

std::string Trailler::TraillerMaker(std::string body) {
    std::string trailler = "";
    trailler.append("10=" );
    trailler.append(traillerCalculated(body));
    return trailler;
}

class AddOrder: public LibData{
public:

    void addOrder(const std::string clOrdID, const std::string price, const std::string qty, std::string Sender, std::string Target) {
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
};

class UpdateOrder: public AddHeader, public Trailler{
    public:
        void UpdateOrd(const std::string clOrdID, std::string price,  std::string qty, std::string Sender, std::string Target, std::string OrderId, std::string NewID, std::string OrderType) {            
            std::string orderData;

            orderData.append("11=" ); // sender ID
            orderData.append(clOrdID);
            orderData.append("41=" ); // sender ID
            orderData.append(NewID);
            orderData.append("^21=3"); // 3 = Manual // 1 = Automated
            orderData.append("^55=TECK"); // nos special symbol
            orderData.append("^54=" );//  1 = Buy, 2 = Sell, //side
            orderData.append(OrderType);
            orderData.append("^60=" );
            orderData.append(GetTime());
            orderData.append("^40=" ); //ordType: 1 = Market, 2 = Limit, 3 = Stop, 4 = Stop limit, ...
            orderData.append( OrderType);
            orderData.append("^37=" ); // ORDER ID
            orderData.append(OrderId);
            orderData.append("^44=" ); // price
            orderData.append(price);
            orderData.append("^38=" ); // qty
            orderData.append(qty);
            orderData.append("^");
            orderData.insert(0, HeaderMaker(orderData, "G", "1", Sender, Target));
            orderData.append(TraillerMaker(orderData));
            std::cout << "UPDATE Data:\n" << orderData << std::endl;
        }
};

class OrderCancel:  public AddHeader, public Trailler{
    public:
        void CancelOrd(const std::string clOrdID, std::string Sender, std::string Target, std::string OrderId, std::string OrderType) {            
            std::string orderData;

            orderData.append("^11=" ); // sender ID
            orderData.append(clOrdID);
            orderData.append("^41=" );
            orderData.append(OrderId); /// check ce champ
            orderData.append("^21=3"); // 3 = Manual // 1 = Automated
            orderData.append("^55=TECK"); // nos special symbol
            orderData.append("^54=" );//  1 = Buy, 2 = Sell, //side
            orderData.append(OrderType);
            orderData.append("^60=" );
            orderData.append(GetTime());
            orderData.append("^40=2" ); //ordType: 1 = Market, 2 = Limit, 3 = Stop, 4 = Stop limit, ...
            orderData.append("^");
            orderData.insert(0, HeaderMaker(orderData, "F", "1", Sender, Target));
            orderData.append(TraillerMaker(orderData));
            std::cout << "CANCEL Data:\n" << orderData << std::endl;
        }
};

class ExReport: public AddHeader, public Trailler{
    public:
        void ExecutionReport( std::string Sender, std::string Target, std::string OrderType, std::string ExecType, std::string OrdStatus, std::string nb, std::string prixMoyen) {            
            std::string orderData;
            orderData.append("^37=8" );
            orderData.append("^17="); ///////////////////// completer 

            orderData.append("^55=TECK"); // nos special symbol
            orderData.append("^54=" );//  1 = Buy, 2 = Sell, //side
            orderData.append(OrderType);
            orderData.append("^150=" );
            orderData.append(ExecType);
            orderData.append("^39=" );
            orderData.append(OrdStatus);
            orderData.append("^151=" ); //////// check this file
            orderData.append("^14=");// nombre d'achat/vente executé
            orderData.append(nb);
            orderData.append("^6="); // prix moyen pour toute les vente de l'ordre
            orderData.append(prixMoyen);
            orderData.append("^");
            orderData.insert(0, HeaderMaker(orderData, "8", "1", Sender, Target));
            orderData.append(TraillerMaker(orderData));
            std::cout << "EXECUTION REPORT Data:\n" << orderData << std::endl;
        }
};

int main(){
    AddOrder addOrder;
    std::string clOrdID = "1";
    std::string price = "100";
    std::string qty = "10";
    addOrder.addOrder(clOrdID, price, qty, "SENDER", "TARGET");
    UpdateOrder updateOrder;
    //updateOrder.UpdateOrd(clOrdID, price, qty, "SENDER", "TARGET", "10", "2");
    updateOrder.UpdateOrd(clOrdID, price,  qty,  "Sender", "Target", "10", "NewID", "2");
    OrderCancel orderCancel;
    orderCancel.CancelOrd(clOrdID, "Sender", "Target", "10", "2");
    ExReport exReport;
    exReport.ExecutionReport("Sender", "Target", "10", "2", "0", "0", "10");
}
