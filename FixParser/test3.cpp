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

        // Formatage de la date et de l'heure
        //return std::put_time(now, "%y%m%d-%H:%M:%S");
        std::stringstream ss;
        ss << std::put_time(now, "%y%m%d-%H:%M:%S");

    // Convertir la sortie de std::put_time en std::string
        std::string dateTimeStr = ss.str();

        return dateTimeStr;
    }
};

class AddHeader: public LibData{
public:
    std::string HeaderMaker(std::string body, std::string MsgType, std::string RqtNb) {
        std::string header = "";
        std::time_t t = std::time(nullptr);
        std::tm* now = std::localtime(&t);

        header.append("8=FIX.4.2^");
        header.append("9=" );
        header.append(std::to_string(body.length()));
        header.append("^35=" );
        header.append(MsgType);
        header.append("^49=Sender^"); // You need to specify sender and target comp ids
        header.append("56=Target^"); // Or adjust accordingly
        header.append("34="  );
        header.append(RqtNb);
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

    void addOrder(const std::string clOrdID, const std::string price, const std::string qty) {
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
        //std::cout << "\n header \n" << header.HeaderMaker(orderData, "D", "1") << std::endl;
        orderData.insert(0, header.HeaderMaker(orderData, "D", "1"));
        //std::cout << "Order Data: " << orderData << std::endl;
        orderData.append(trailler.TraillerMaker(orderData));
        std::cout << "Order Data:\n" << orderData << std::endl;
    }
};

int main(int a, char** av){
    AddOrder addOrder;
    std::string clOrdID = "1";
    std::string price = "100";
    std::string qty = "10";
    addOrder.addOrder(clOrdID, price, qty);
}
