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
            buyOrdersList.push_back(Order(clientID, quantity, price));
            updateBuyOrders();
        }

        void addSellOrder(int clientID, int quantity, int price) {
        sellOrders.push_back(Order(clientID, quantity, price));
        updateSellOrders();
        }

        void displayOrderBook() {
            std::cout << "   Achat:\t\t\t\tVente:\n";
            displayOrders(achatList, venteList);

            std::cout << "detail ajout order";
            std::cout << "\nAchat (details):\t\tVente (details):\n";

        }

        void displayOrdersDetails() {
            std::cout << "   Achat (details):\t\t\t\tVente (details):\n";
            displayOrdersDetails(buyOrdersList, sellOrders);
        }
    
    private:
        int MyID = 0;
        std::vector<Order> buyOrders;
        std::vector<Order> buyOrdersList;
        std::vector<Order> sellOrders;

        std::vector<std::vector<int>> achatList;
        std::vector<std::vector<int>> venteList;
        
        void updateBuyOrders() {
            std::sort(buyOrders.begin(), buyOrders.end(), [](const Order& a, const Order& b) {
                return a.price > b.price;
            });

            mergeOrders(buyOrders, achatList);
        }

        void updateSellOrders() {
            std::sort(sellOrders.begin(), sellOrders.end(), [](const Order& a, const Order& b) {
                return a.price < b.price;
            });

            mergeOrders(sellOrders, venteList);
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

        void displayOrders(const std::vector<std::vector<int>>& orderListAchat, const std::vector<std::vector<int>>& orderListVente) {
            int count = 0;
            int maxSize = 10;

            for (int i = 0; i < maxSize; ++i) {
                if (i < orderListAchat.size()) {
                    std::cout << "Client ID (Achat): " << orderListAchat[i][0] << ", Quantite: " << orderListAchat[i][1] << ", Prix: " << orderListAchat[i][2];
                    std::cout << "\t\t\t";
                }
                if (i < orderListVente.size()) {
                    std::cout << "Client ID (Vente): " << orderListVente[i][0] << ", Quantite: " << orderListVente[i][1] << ", Prix: " << orderListVente[i][2];
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

};

int main() {
    OrderBook orderBook;

    // Ajout de quelques ordres pour tester
    orderBook.addBuyOrder(1, 5, 100);
    orderBook.addBuyOrder(2, 10, 95);
    orderBook.addBuyOrder(3, 8, 100);
    orderBook.displayOrdersDetails();
    std::cout << "________________";
    orderBook.addSellOrder(4, 7, 105);
    orderBook.addSellOrder(5, 12, 98);
    orderBook.addSellOrder(6, 6, 105);
    orderBook.displayOrdersDetails();
    // Affichage des 10 premières lignes du carnet d'ordres
    orderBook.displayOrderBook();

    orderBook.addSellOrder(4, 30, 15);
    orderBook.addSellOrder(5, 12, 100);
    orderBook.addSellOrder(6, 6, 10);
    orderBook.addBuyOrder(1, 30, 60);
    orderBook.addBuyOrder(2, 10, 95);
    orderBook.addBuyOrder(3, 8, 150);

    std::cout << "---------------------------------------------";
    orderBook.displayOrderBook();
    orderBook.addSellOrder(4, 7, 105);
    orderBook.addSellOrder(5, 12, 98);
    orderBook.addSellOrder(6, 6, 105);
    orderBook.addBuyOrder(1, 100, 20);
    orderBook.addBuyOrder(2, 40, 95);
    orderBook.addBuyOrder(3, 18, 30);
    
    std::cout << "---------------------------------------------";
    orderBook.displayOrderBook();
    std::cout << "________________";
    orderBook.displayOrdersDetails();
    return 0;
}