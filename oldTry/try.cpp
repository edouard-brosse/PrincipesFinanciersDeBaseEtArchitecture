#include <iostream>
#include <vector>
#include <algorithm>

//ORDER BOOK
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
            MyID ++;
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
        displayOrders(achatList, venteList);
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

    void manageSellMarcket() {
    if (buyOrders.empty() || venteList.empty() || venteList[0].empty()) {
        return;
    }
    for (int y = 0; y < buyOrders.size(); y ++) {
    //for (const auto& : buyOrders)
        if (buyOrders[y].price >= venteList[0][2]) {
            if (buyOrders[y].quantity < venteList[0][1]) {
                std::cout << "ACHAT de : " << venteList[0][1] - buyOrders[y].quantity << "\t au prix de " << venteList[0][2] << " achat ID " << buyOrders[y].clientID << " vente ID: " << venteList[0][3] <<"\n";

                venteList[0][1] -= buyOrders[y].quantity;
                removeBuyOrder(venteList[0][3]);
            } else if (buyOrders[y].quantity == venteList[0][1]) {
                std::cout << "ACHAT de : " << buyOrders[y].quantity << "\t au prix de " << venteList[0][2] << " achat ID " << buyOrders[y].clientID << " vente ID: " << venteList[0][3]  << "\n";
                //venteList[0][1] -= buy.quantity;
                removeBuyOrder(venteList[0][3]);
                removeBuyOrder(buyOrders[y].ID);
            } else {
                std::cout << "ACHAT de : " << buyOrders[y].quantity - venteList[0][1] << "\t au prix de " << venteList[0][2] << " achat ID " << buyOrders[y].clientID << " vente ID: " << venteList[0][3] << "\n";
                buyOrders[y].quantity -= venteList[0][1];
                removeBuyOrder(buyOrders[y].ID);
            }
            // Continue processing if there are more potential matches
            manageSellMarcket();
        }
    }

    // void manageSellMarcket() {
    // if (buyOrders.empty() || venteList.empty() || venteList[0].empty()) {
    //     return;
    // }

    // for (auto it = buyOrders.begin(); it != buyOrders.end(); ) {
    //     auto& buy = *it;

    //     if (buy.price >= venteList[0][2]) {
    //         if (buy.quantity < venteList[0][1]) {
    //             std::cout << "ACHAT de : " << venteList[0][1] - buy.quantity << "\t au prix de " << venteList[0][2] << " achat ID " << buy.clientID << " vente ID: " << venteList[0][0] <<"\n";

    //             venteList[0][1] -= buy.quantity;
    //             it = buyOrders.erase(it);
    //         } else if (buy.price == venteList[0][2]) {
    //             std::cout << "ACHAT de : " << buy.quantity << "\t au prix de " << venteList[0][2] << " achat ID " << buy.clientID << " vente ID: " << venteList[0][0]  << "\n";
    //             venteList[0][1] -= buy.quantity;
    //             it = buyOrders.erase(it);
    //         } else {
    //             std::cout << "ACHAT de : " << buy.quantity - venteList[0][1] << "\t au prix de " << venteList[0][2] << " achat ID " << buy.clientID << " vente ID: " << venteList[0][0] << "\n";
    //             buy.quantity -= venteList[0][1];
    //             it = buyOrders.erase(it);
    //         }
    //         // Continue processing if there are more potential matches
    //         manageSellMarcket();
    //     } else {
    //         ++it;
    //     }
    // }
    // No need to call updateBuyOrders() here, it's already called within removeBuyOrder
}



    // void manageSellMarcket(){
    //     if(buyOrders == NULL || venteList[0] == NULL){
    //         return;
    //     }
    //     for (const auto& buy: buyOrders){
    //         if (buy.price >= venteList[0].price){
    //             if(buy.quantity < venteList[0].quantity){
    //                 std::cout << "ACHAT de : " << venteList[0].quantity - buy.quantity << "\t au prix de" << venteList[0].price;
    //                 venteList[0].quantity -= buy.quantity;
    //                 removeBuyOrder(venteList[0].ID);
    //             }else if (buy.price == venteList[0].price){
    //                 std::cout << "ACHAT de : " <<  buy.quantity << "\t au prix de" << venteList[0].price;
    //                 venteList[0].quantity -= buy.quantity;
    //                 removeBuyOrder(venteList[0].ID);
    //                 removeBuyOrder(buy.ID);
    //             }else{
    //                 std::cout << "ACHAT de : " << buy.quantity - venteList[0].quantity << "\t au prix de" << venteList[0].price;
    //                 buy.quantity =- venteList[0].quantity
    //                 removeBuyOrder(buy.ID);
    //             }
    //             manageSellMarcket();
    //         }
    //             //MarketOperation(buy.ID);
    //     }
    //     //updateBuyOrders();
    // }
    
    private:
        int MyID = 0;
        std::vector<Order> buyOrders;
        std::vector<Order> sellOrders;

        std::vector<std::vector<int>> achatList;
        std::vector<std::vector<int>> venteList;
        
        void updateBuyOrders() {
            //mergeOrders(buyOrders, achatList);

            std::sort(achatList.begin(), achatList.end(), [](const auto& a, const auto& b) {
                return a[2] > b[2];
            });
            std::cout << "UPDATE SORT\n" ;
            mergeOrders(buyOrders, achatList);
        }

        void updateSellOrders() {
            //mergeOrders(sellOrders, venteList);

            std::sort(venteList.begin(), venteList.end(), [](const auto& a, const auto& b) {
                return a[2] < b[2];
            });
            mergeOrders(buyOrders, achatList);
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
                std::cout << "Client ID (Achat): " << orderListAchat[i].clientID << ", Quantite: " << orderListAchat[i].quantity << ", Prix: " << orderListAchat[i].price << ", OrderID: "<< orderListAchat[i].ID;
                std::cout << "\t\t\t";
            }
            if (i < orderListVente.size()) {
                std::cout << "Client ID (Vente): " << orderListVente[i].clientID << ", Quantite: " << orderListVente[i].quantity << ", Prix: " << orderListVente[i].price << ", OrderID: "<< orderListVente[i].ID;
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
    orderBook.addBuyOrder(1, 5, 1000);
    orderBook.addBuyOrder(1, 5, 100);
    orderBook.addBuyOrder(2, 10, 95);
    orderBook.addBuyOrder(3, 8, 100);
    orderBook.addBuyOrder(7, 3, 100);
    // std::cout << "_______| ManageSellMarcket |_________\n";
    // orderBook.manageSellMarcket();
    // orderBook.displayOrdersDetails();
    // std::cout << "_______| 2 |_________\n";
    orderBook.addSellOrder(4, 7, 105);
    orderBook.addSellOrder(5, 12, 98);
    orderBook.addSellOrder(6, 6, 105);

    orderBook.displayOrdersDetails();
    std::cout << "\n_______| ManageSellMarcket |_________\n";
    //orderBook.manageSellMarcket();
    std::cout << "\n_______| 2 |_________\n";
    orderBook.displayOrdersDetails();
    //orderBook.displayOrdersDetails();
    // Affichage des 10 premières lignes du carnet d'ordres
    std::cout << "\n_______| ORDER BOOK |_________\n";
    orderBook.displayOrderBook();

    // orderBook.addSellOrder(4, 30, 15);
    // orderBook.addSellOrder(5, 12, 100);
    // orderBook.addSellOrder(6, 6, 10);
    // orderBook.addBuyOrder(1, 30, 60);
    // orderBook.addBuyOrder(2, 10, 95);
    // orderBook.addBuyOrder(3, 8, 150);

    // //std::cout << "---------------------------------------------";
    // //orderBook.displayOrderBook();
    // orderBook.addSellOrder(4, 7, 105);
    // orderBook.addSellOrder(5, 12, 98);
    // orderBook.addSellOrder(6, 6, 105);
    // orderBook.addBuyOrder(1, 100, 20);
    // orderBook.addBuyOrder(2, 40, 95);
    // orderBook.addBuyOrder(3, 18, 30);
    
    // std::cout << "---------------------------------------------\n";
    // orderBook.displayOrderBook();
    // orderBook.removeBuyOrder(0);
    // orderBook.removeBuyOrder(17);
    // std::cout << "---------------------------------------------\n";
    // orderBook.displayOrderBook();
    // //std::cancelOrder(14);
    // std::cout << "_______________________________________________________________\n";
    // orderBook.displayOrdersDetails();
    // std::cout << "''''''''''''''''''''''''''''''| id 2 |''''''''''''''''''''''''''''''''''''\n";
    orderBook.displayClient(2);
    return 0;
}