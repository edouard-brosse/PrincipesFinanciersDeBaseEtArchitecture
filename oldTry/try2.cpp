#include <iostream>
#include <vector>
#include <algorithm>

// ORDER BOOK
class OrderBook {
public:
    struct Order {
        int clientID;
        int quantity;
        int price;
        int ID;

        Order(int id, int qty, int prc, int myID) : clientID(id), quantity(qty), price(prc), ID(myID) {}
    };

    void addBuyOrder(int clientID, int quantity, int price) {
        buyOrders.push_back(Order(clientID, quantity, price, MyID));
        MyID++;
        updateBuyOrders();
    }

    void addSellOrder(int clientID, int quantity, int price) {
        sellOrders.push_back(Order(clientID, quantity, price, MyID));
        MyID++;
        updateSellOrders();
    }

    void removeBuyOrder(int ID) {
        auto it = std::remove_if(buyOrders.begin(), buyOrders.end(), [ID](const Order& order) {
            return order.ID == ID;
        });
        buyOrders.erase(it, buyOrders.end());
        updateBuyOrders();
    }

    void displayOrderBook() {
        std::cout << "Sort Merge List\nAchat:\t\t\t\t\t\tVente:\n";
        displayOrders(buyOrders, sellOrders);
    }

    void displayOrdersDetails() {
        std::cout << "Order Detail\nAchat (details):\t\t\t\tVente (details):\n";
        displayOrdersDetails(buyOrders, sellOrders);
    }

    void displayClient(int cliId) {
        std::cout << "Ordres d'achat pour le client ID " << cliId << " :\n";

        for (const auto& order : buyOrders) {
            if (order.clientID == cliId) {
                std::cout << "Client ID (Achat): " << order.clientID << ", Quantite: " << order.quantity << ", Prix: " << order.price << ", OrderID: " << order.ID << "\n";
            }
        }
    }

    // void manageSellMarket() {
    //     if (buyOrders.empty() || sellOrders.empty()) {
    //         return;
    //     }

    //     for (auto it = buyOrders.begin(); it != buyOrders.end();) {
    //         auto& buy = *it;

    //         if (buy.price >= sellOrders[0].price) {
    //             if (buy.quantity < sellOrders[0].quantity) {
    //                 std::cout << "ACHAT de : " << sellOrders[0].quantity - buy.quantity << "\t au prix de " << sellOrders[0].price
    //                           << " achat ID " << buy.clientID << " vente ID: " << sellOrders[0].ID << "\n";

    //                 sellOrders[0].quantity -= buy.quantity;
    //                 it = buyOrders.erase(it);
    //             } else if (buy.quantity == sellOrders[0].quantity) {
    //                 std::cout << "ACHAT de : " << buy.quantity << "\t au prix de " << sellOrders[0].price << " achat ID " << buy.clientID << " vente ID: " << sellOrders[0].ID << "\n";

    //                 sellOrders[0].quantity -= buy.quantity;
    //                 it = buyOrders.erase(it);
    //                 // Si la quantité achetée est égale à la quantité vendue, supprimez également l'ordre de vente
    //                 sellOrders.erase(sellOrders.begin());
    //             } else {
    //                 std::cout << "ACHAT de : " << buy.quantity - sellOrders[0].quantity << "\t au prix de " << sellOrders[0].price
    //                           << " achat ID " << buy.clientID << " vente ID: " << sellOrders[0].ID << "\n";

    //                 buy.quantity -= sellOrders[0].quantity;
    //                 it = buyOrders.erase(it);
    //                 // Supprimez également l'ordre de vente car il est entièrement rempli
    //                 sellOrders.erase(sellOrders.begin());
    //             }
    //             // Continue processing if there are more potential matches
    //             manageSellMarket();
    //         } else {
    //             ++it;
    //         }
    //     }
    // }

private:
    int MyID = 0;
    std::vector<Order> buyOrders;
    std::vector<Order> sellOrders;

    void updateBuyOrders() {
        std::sort(buyOrders.begin(), buyOrders.end(), [](const auto& a, const auto& b) {
            return a.price > b.price;
        });
    }

    void updateSellOrders() {
        std::sort(sellOrders.begin(), sellOrders.end(), [](const auto& a, const auto& b) {
            return a.price < b.price;
        });
    }

    void displayOrders(const std::vector<Order>& orderListAchat, const std::vector<Order>& orderListVente) {
        int count = 0;
        int maxSize = 10;

        for (int i = 0; i < maxSize; ++i) {
            if (i < orderListAchat.size()) {
                std::cout << "Client ID (Achat): " << orderListAchat[i].clientID << ", Quantite: " << orderListAchat[i].quantity << ", Prix: " << orderListAchat[i].price;
                std::cout << "\t\t\t";
            }
            if (i < orderListVente.size()) {
                std::cout << "Client ID (Vente): " << orderListVente[i].clientID << ", Quantite: " << orderListVente[i].quantity << ", Prix: " << orderListVente[i].price;
            }
            std::cout << "\n";
            count++;
            if (i >= orderListAchat.size() && i >= orderListVente.size()) {
                break;
            }
        }
    }

    void displayOrdersDetails(const std::vector<Order>& orderListAchat, const std::vector<Order>& orderListVente) {
        int count = 0;
        int maxSize = 10;

        for (int i = 0; i < maxSize; ++i) {
            if (i < orderListAchat.size()) {
                std::cout << "Client ID (Achat): " << orderListAchat[i].clientID << ", Quantite: " << orderListAchat[i].quantity << ", Prix: " << orderListAchat[i].price << ", OrderID: " << orderListAchat[i].ID;
                std::cout << "\t\t\t";
            }
            if (i < orderListVente.size()) {
                std::cout << "Client ID (Vente): " << orderListVente[i].clientID << ", Quantite: " << orderListVente[i].quantity << ", Prix: " << orderListVente[i].price << ", OrderID: " << orderListVente[i].ID;
            }
            std::cout << "\n";
            count++;
            if (i >= orderListAchat.size() && i >= orderListVente.size()) {
                break;
            }
        }
    }
};

int main() {
    OrderBook orderBook;

    orderBook.addBuyOrder(1, 5, 100);
    orderBook.addBuyOrder(2, 10, 95);
    orderBook.addBuyOrder(3, 8, 100);
    orderBook.addBuyOrder(7, 3, 100);

    orderBook.addSellOrder(4, 7, 105);
    orderBook.addSellOrder(5, 12, 98);
    orderBook.addSellOrder(6, 6, 105);

    std::cout << "\torderbook\n";
    orderBook.displayOrderBook();
    //std::cout << "\tSellMarket\n";
    //orderBook.manageSellMarket();
    std::cout << "\tOrdersDetails\n";
    orderBook.displayOrdersDetails();

    return 0;
}
