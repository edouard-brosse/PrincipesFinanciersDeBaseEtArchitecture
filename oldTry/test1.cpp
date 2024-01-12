#include <iostream>
#include <vector>
#include <algorithm>

class OrderBook {
public:
    struct Order {
        int clientID;
        int quantity;
        int price;

        Order(int id, int qty, int prc) : clientID(id), quantity(qty), price(prc) {}
    };

    void addBuyOrder(int clientID, int quantity, int price) {
        buyOrders.push_back(Order(clientID, quantity, price));
        updateBuyOrders();
    }

    void addSellOrder(int clientID, int quantity, int price) {
        sellOrders.push_back(Order(clientID, quantity, price));
        updateSellOrders();
    }

    void displayOrderBook() {
        std::cout << "   Achat:\t\t\tVente:\n";
        displayOrders(achatList, venteList);

        std::cout << "\nAchat (détails):\t\tVente (détails):\n";
        displayDetailedOrders(achat, vente);
    }

private:
    void updateBuyOrders() {
        std::sort(buyOrders.begin(), buyOrders.end(), [](const Order& a, const Order& b) {
            return a.price > b.price;
        });

        mergeOrders(buyOrders, achatList);
        mergeDetailedOrders(buyOrders, achat);
    }

    void updateSellOrders() {
        std::sort(sellOrders.begin(), sellOrders.end(), [](const Order& a, const Order& b) {
            return a.price < b.price;
        });

        mergeOrders(sellOrders, venteList);
        mergeDetailedOrders(sellOrders, vente);
    }

    void mergeOrders(const std::vector<Order>& orders, std::vector<std::vector<int>>& orderList) {
        orderList.clear();

        for (const auto& order : orders) {
            bool merged = false;

            for (auto& row : orderList) {
                if (order.price == row[2]) {
                    row[0]++;
                    row[1] += order.quantity;
                    merged = true;
                    break;
                }
            }

            if (!merged) {
                orderList.push_back({1, order.quantity, order.price});
            }
        }
    }

    void mergeDetailedOrders(const std::vector<Order>& orders, std::vector<std::vector<int>>& detailedOrderList) {
        for (const auto& order : orders) {
            bool merged = false;

            for (auto& row : detailedOrderList) {
                if (order.price == row[2]) {
                    row[0]++;
                    row[1] += order.quantity;
                    row[3] += order.price; // Ajout du prix total pour le calcul de la moyenne
                    merged = true;
                    break;
                }
            }

            if (!merged) {
                detailedOrderList.push_back({1, order.quantity, order.price, order.price});
            }
        }
    }

    void displayOrders(const std::vector<std::vector<int>>& orderListAchat, const std::vector<std::vector<int>>& orderListVente) {
        int count = 0;
        for (int i = 0; i < 10; ++i) {
            std::cout << "Client ID: " << orderListAchat[i][0] << ", Quantité: " << orderListAchat[i][1] << ", Prix: " << orderListAchat[i][2];
            std::cout << "\t\t\t";
            std::cout << "Client ID: " << orderListVente[i][0] << ", Quantité: " << orderListVente[i][1] << ", Prix: " << orderListVente[i][2] << "\n";
            count++;
        }
    }

    void displayDetailedOrders(const std::vector<std::vector<int>>& detailedOrderListAchat, const std::vector<std::vector<int>>& detailedOrderListVente) {
        int count = 0;
        for (int i = 0; i < 10; ++i) {
            std::cout << "Client ID: " << detailedOrderListAchat[i][0] << ", Quantité: " << detailedOrderListAchat[i][1] << ", Prix: " << detailedOrderListAchat[i][2];
            std::cout << "\t\t";
            std::cout << "Client ID: " << detailedOrderListVente[i][0] << ", Quantité: " << detailedOrderListVente[i][1] << ", Prix: " << detailedOrderListVente[i][2] << "\n";
            count++;
        }
    }

    std::vector<Order> buyOrders;
    std::vector<Order> sellOrders;

    std::vector<std::vector<int>> achatList;
    std::vector<std::vector<int>> venteList;

    std::vector<std::vector<int>> achat;
    std::vector<std::vector<int>> vente;
};

int main() {
    OrderBook orderBook;

    // Ajout de quelques ordres pour tester
    orderBook.addBuyOrder(1, 5, 100);
    orderBook.addBuyOrder(2, 10, 95);
    orderBook.addBuyOrder(3, 8, 100);

    orderBook.addSellOrder(4, 7, 105);
    orderBook.addSellOrder(5, 12, 98);
    orderBook.addSellOrder(6, 6, 105);

    // Affichage des 10 premières lignes du carnet d'ordres
    orderBook.displayOrderBook();

    return 0;
}
