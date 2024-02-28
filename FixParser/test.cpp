#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

class LibData {
private:
    std::unordered_map<std::string, std::vector<std::pair<std::string, std::string>>> dataMap;

public:
    void initLib() {
        // Initialize header fields
        dataMap["HeaderLib"] = {
            {"8", "BeginString"},
            {"9", "BodyLength"},
            {"35", "MsgType"},
            {"49", "SenderCompID"},
            {"56", "TargetCompID"},
            {"34", "MsgSeqNum"},
            {"52", "SendingTime"}
        };

        // Initialize body fields
        dataMap["BodyLib"] = {
            {"11", "ClOrdID"},
            {"21", "HandlInst"},
            {"55", "Symbol"},
            {"54", "Side"},
            {"60", "TransactTime"},
            {"40", "OrdType"}
        };

        // Initialize trailer fields
        dataMap["TrailLib"] = {
            {"10", "Checksum"}
        };
    }

    void printData() {
        for (const auto& entry : dataMap) {
            std::cout << entry.first << ":\n";
            for (const auto& pair : entry.second) {
                std::cout << "  " << pair.first << ": " << pair.second << "\n";
            }
        }
    }
};

// Subclass for adding orders
class AddOrder : public LibData {
private:

public:

};

// Subclass for updating orders
class UpdateOrder : public LibData {
private:

public:

};

int main() {
    AddOrder addOrderInstance;
    addOrderInstance.initLib();

    UpdateOrder updateOrderInstance;
    updateOrderInstance.initLib();

    std::cout << "Add Order Data:\n";
    addOrderInstance.printData();

    std::cout << "\nUpdate Order Data:\n";
    updateOrderInstance.printData();

    return 0;
}
