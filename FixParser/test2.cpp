#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <ctime>


class LibData {
private:
    std::unordered_map<std::string, std::vector<std::pair<std::string, std::string>>> dataMap;

public:
    void initLib() {
        dataMap["HeaderLib"] = {
            {"8", "BeginString"},
            {"9", "BodyLength"},
            {"35", "MsgType"},
            {"49", "SenderCompID"},
            {"56", "TargetCompID"},
            {"34", "MsgSeqNum"},
            {"52", "SendingTime"}
        };

        dataMap["BodyLib"] = {
            {"11", "ClOrdID"},
            {"21", "HandlInst"},
            {"55", "Symbol"},
            {"54", "Side"},
            {"60", "TransactTime"},
            {"40", "OrdType"}
        };

        dataMap["TrailLib"] = {
            {"10", "Checksum"}
        };
    }

    const std::vector<std::pair<std::string, std::string>>& getData(const std::string& category) const {
        return dataMap.at(category);
    }

    void setData(const std::string& category, const std::vector<std::pair<std::string, std::string>>& data) {
        dataMap[category] = data;
    }

    void printData() const {
        for (const auto& entry : dataMap) {
            std::cout << entry.first << ":\n";
            for (const auto& pair : entry.second) {
                std::cout << "  " << pair.first << ": " << pair.second << "\n";
            }
        }
    }
};


class AddHeader: LibData {
    private:

    public:
        std::string HeaderMaker(std::string body, std::string MsgType, std::string RqtNb);
};

AddHeader::HeaderMaker(std::string body, std::string MsgType, std::string RqtNb){
    std::string header = "";
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);

    header.append("8=FIX.4.2^");
    header.append("9="+ body.length().to_string()+ "^");
    header.append("35=" + MsgType + "^");
    header.append("49=" + + "^");
    header.append("56=" + + "^");
    header.append("34=" + RqtNb + "^");
    header.append("52=" + now->tm_hour + ":" + now->tm_min + ":" + now->tm_sec + "^");
    
    return header;
}

class AddTrailler: LibData {
    private:
        std::string traillerCalculated(std::string body);
    public:
        std::string TraillerMaker(std::string body);
};

std::string traillerCalculated(std::string body){
    std::string trailler = "";
    int sum = 0;
    for (char c : message) {
        sum += c; // Ajoute la valeur ASCII de chaque caractère
    }
    int temp = sum % 256;
    trailer = std::string(3 - temp.length(), '0'); // Retourne le résultat modulo 256
    return trailler;
}

AddTrailler::TraillerMaker(std::string body){
    std::string trailler = "";
    trailler.append("10=" + traillerCalculated(body) + "^");
    return trailler;
}

class AddOrder : public LibData {
public:
    void addOrder(const std::string& clOrdID, const std::string& symbol, const std::string& side, const std::string& ordType) {
        auto currentTime = std::chrono::system_clock::now();
        std::time_t currentTime_t = std::chrono::system_clock::to_time_t(currentTime);


        std::string body = " ";
        std::vector<std::pair<std::string, std::string>> orderData;
        orderData.push_back({"11", clOrdID, "^"}); // sender ID
        orderData.push_back({"21", "3", "^"}); // 3 = Manual // 1 = Automated 
        orderData.push_back({"55", "[N/A]", "^"}); // nos special symbol
        orderData.push_back({"54", "1", "^"});//  1 = Buy, 2 = Sell, 
        orderData.push_back({"60", std::asctime(std::gmtime(&currentTime_t)).to_string, "^"});
        orderData.push_back({"40", "2" , "^"}); //ordType: 1 = Market, 2 = Limit, 3 = Stop, 4 = Stop limit, ...
        orderData.push_back(AddHeader::HeaderMaker(body, "D", "1")); 
        

        setData("BodyLib", orderData);
    }
};

//class AddOrder : public LibData {
//private:
//
//public:
//};



//class UpdateOrder : public LibData {
//private: 
//
//public:
//
//};

int main(int a, char av){
    AddOrder::addOrder()
}


//int main() {
//    AddOrder addOrderInstance;
//    addOrderInstance.initLib();
//
//    UpdateOrder updateOrderInstance;
//    updateOrderInstance.initLib();
//
//    std::cout << "Add Order Data:\n";
//    addOrderInstance.printData();
//
//    std::cout << "\nUpdate Order Data:\n";
//    updateOrderInstance.printData();
//
//    return 0;
//}  