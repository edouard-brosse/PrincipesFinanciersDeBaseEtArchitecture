#include <iostream>
#include <vector>
#include <algorithm>

//ORDER BOOK
class OrderBook {
    public:
        struct Order {
            int clientID; // ou nb de client selon la fonction
            int quantity;
            int price;
            int ID;
            Order(int id, int qty, int prc, int myID) : clientID(id), quantity(qty), price(prc), ID(myID) {}
        };
        // tout foutre sur la mm variable avec une "ID"  a la fin pour separer l'achat de la vente
        // puis tout trier au niveau des deux listes suivante
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

        void removeOrderById(std::vector<Order>& orders, int ID) {
            auto it = std::remove_if(orders.begin(), orders.end(), [ID](const Order& order) {
                return order.ID == ID;
            });
            orders.erase(it, orders.end());
        }

    
    void displayOrderBook() {
        std::cout << "Sort Merge List| TEST |\nAchat:\t\t\t\t\t\tVente:\n";
        displayOrders(achatList, venteList);
    }

    void displayOrdersDetails() {
        std::cout << "Order Detail\nAchat (details):\t\t\t\tVente (details):\n";
        displayOrdersDetails( buyOrders, sellOrders);
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
        if (buyOrders.empty()|| sellOrders.empty() || achatList.empty() || venteList.empty()) {
            return;
        }
        std::cout << "======================== |PASSE |===============\n";
        //displayOrdersDetails();
        //std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!";
        //displayOrderBook();
        for (int y = 0; y < achatList.size(); y ++) {
           if (achatList[y].price >= venteList[0].price){
                if (achatList[y].quantity < venteList[0].quantity) {
                    std::cout << "=== | achat < vente |===\n";
                    std::cout << "ACHAT de : " <<  achatList[y].quantity << "\t au prix de " << venteList[0].price << " achat ID " << achatList[y].clientID << " vente ID: " << venteList[0].clientID <<"\n";
                    venteList[0].quantity -= achatList[y].quantity;
                    //removeBuyOrder(venteList[0].ID);
                    removeOrderById(venteList, venteList[0].ID);
                } else if (achatList[y].quantity == venteList[0].quantity) {
                    std::cout << "=== | achat == vente |===\n";
                    std::cout << "ACHAT de : " << achatList[y].quantity << "\t au prix de " << venteList[0].price << " achat ID " << achatList[y].clientID << " vente ID: " << venteList[0].ID  << "\n";
                    venteList[0].quantity -= achatList[y].quantity;
                    //removeBuyOrder(venteList[0].ID);
                    //removeBuyOrder(achatList[y].ID);
                    removeOrderById(venteList, venteList[0].ID);
                    removeOrderById(achatList, achatList[y].ID);
                } else if (achatList[y].quantity > venteList[0].quantity) {
                    std::cout << "=== | achat > vente |===\n";
                    std::cout << "ACHAT de : " << venteList[0].quantity << "\t au prix de " << venteList[0].price << " achat ID " << achatList[y].clientID << " vente ID: " << venteList[0].ID << "\n";
                    std::cout << "nb vente : " << venteList[0].quantity << " nb achat "<< achatList[y].quantity << " Result : " << (achatList[y].quantity - venteList[0].quantity) << "\n";
                    achatList[y].quantity = achatList[y].quantity -= venteList[0].quantity;
                    //removeBuyOrder(achatList[y].ID);
                    removeOrderById(achatList, achatList[y].ID);
                }
            // Continue processing if there are more potential matches
            }
        }
    }

    void BuyOp(){

    }

    void SellOp(){
    }

    private:
        int MyID = 0;
        std::vector<Order> buyOrders;
        std::vector<Order> sellOrders;

        std::vector<Order> achatList;
        std::vector<Order> venteList;
        
        void updateBuyOrders() {
            mergeOrders(buyOrders, achatList);

            std::sort(achatList.begin(), achatList.end(), [](const auto& a, const auto& b) -> bool {
                return a.price > b.price;
            });
            std::cout << "UPDATE SORT\n" ;
            //mergeOrders(buyOrders, achatList);
        }

        void updateSellOrders() {
            mergeOrders(sellOrders, venteList);

            std::sort(venteList.begin(), venteList.end(), [](const auto& a, const auto& b) -> bool {
                return a.price < b.price;
            });
            std::cout << "UPDATE Sale SORT\n" ;
            //mergeOrders(buyOrders, achatList);
        }

        void mergeOrders(const std::vector<Order>& orders, std::vector<Order>& orderList) {
            orderList.clear();

            for (const auto& order : orders) {
                bool merged = false;

                for (auto& row : orderList) {
                    if (order.price == row.price) {
                        row.clientID ++;
                        row.quantity += order.quantity;  // Corrected line
                        merged = true;
                        break;
                    }
                }

                if (!merged) {
                    orderList.push_back(Order(1, order.quantity, order.price, 0));
                }
            }
        }


        void displayOrders(const std::vector<Order>& orderListAchat, const std::vector<Order>& orderListVente) {
            int count = 0;
            int maxSize = 10;

            for (int i = 0; i < maxSize; ++i) {
                if (i < orderListAchat.size()) {
                    std::cout << "NB client (Achat): " << orderListAchat[i].clientID << ", Quantite: " << orderListAchat[i].quantity << ", Prix: " << orderListAchat[i].price;
                    std::cout << "\t\t\t";
                }
                if (i < orderListVente.size()) {
                    std::cout << "NB client (Vente): " << orderListVente[i].clientID << ", Quantite: " << orderListVente[i].quantity << ", Prix: " << orderListVente[i].price;
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
    //orderBook.addBuyOrder(1, 5, 1000);
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
    std::cout << "\n_______| ORDER BOOK |_________\n";
    orderBook.displayOrderBook();
    //std::cout << "\n_______| ManageSellMarcket |_________\n";
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
    // //std::cancelOrder(14);
    // std::cout << "_______________________________________________________________\n";
    // orderBook.displayOrdersDetails();
    // std::cout << "''''''''''''''''''''''''''''''| id 2 |''''''''''''''''''''''''''''''''''''\n";
    orderBook.displayClient(2);
    return 0;
}