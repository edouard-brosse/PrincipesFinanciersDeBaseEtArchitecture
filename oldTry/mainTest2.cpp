#include <iostream>
#include <vector>
#include <algorithm>

class OrderBook {
public:
    // Structure pour représenter un ordre
    struct Order {
        int clientID;
        int quantity;
        int price;

        Order(int id, int qty, int prc) : clientID(id), quantity(qty), price(prc) {}
    };

    // Fonction pour ajouter un ordre d'achat
    void addBuyOrder(int clientID, int quantity, int price) {
        buyOrders.push_back(Order(clientID, quantity, price));
        updateBuyOrders();
    }

    // Fonction pour ajouter un ordre de vente
    void addSellOrder(int clientID, int quantity, int price) {
        sellOrders.push_back(Order(clientID, quantity, price));
        updateSellOrders();
    }

    // Fonction pour afficher les 10 premières lignes des carnets d'ordres
    void displayOrderBook() {
        std::cout << "Achat:\n";
        displayOrders(achatList);

        std::cout << "\nVente:\n";
        displayOrders(venteList);
    }

private:
    // Fonction pour mettre à jour les carnets d'ordres d'achat après chaque ajout
    void updateBuyOrders() {
        std::sort(buyOrders.begin(), buyOrders.end(), [](const Order& a, const Order& b) {
            return a.price > b.price;
        });

        mergeOrders(buyOrders, achatList);
    }

    // Fonction pour mettre à jour les carnets d'ordres de vente après chaque ajout
    void updateSellOrders() {
        std::sort(sellOrders.begin(), sellOrders.end(), [](const Order& a, const Order& b) {
            return a.price < b.price;
        });

        mergeOrders(sellOrders, venteList);
    }

    // Fonction pour fusionner les ordres avec le même prix
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

    // Fonction pour afficher les ordres
    void displayOrders(const std::vector<std::vector<int>>& orderList) {
        int count = 0;
        for (const auto& row : orderList) {
            std::cout << "Client ID: " << row[0] << ", Quantité: " << row[1] << ", Prix: " << row[2] << "\n";
            count++;
            if (count == 10) break;
        }
    }

    // Carnets d'ordres
    std::vector<Order> buyOrders;  // Liste des ordres d'achat
    std::vector<Order> sellOrders; // Liste des ordres de vente

    // Carnets d'ordres fusionnés
    std::vector<std::vector<int>> achatList; // Carnet d'ordres d'achat fusionné
    std::vector<std::vector<int>> venteList; // Carnet d'ordres de vente fusionné
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
