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
    header.append("35=" +  + "^");
    header.append("56=" + + "^");
    header.append("34=" + RqtNb + "^");
    header.append("52=" +  + "^");
    
    return header;
}

class AddOrder : public LibData {
public:
    void addOrder(const std::string& clOrdID, const std::string& symbol, const std::string& side, const std::string& transactTime, const std::string& ordType) {
        std::vector<std::pair<std::string, std::string>> orderData;
        orderData.push_back({"11", clOrdID});
        orderData.push_back({"55", symbol});
        orderData.push_back({"54", side});
        orderData.push_back({"60", transactTime});
        orderData.push_back({"40", ordType});

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