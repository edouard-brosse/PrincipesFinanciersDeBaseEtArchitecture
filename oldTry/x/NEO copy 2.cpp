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
            int category; // 0 pour achat, 1 pour vente
            Order(int id, int qty, int prc, int myID, int Category) : clientID(id), quantity(qty), price(prc), ID(myID), category(Category) {}
        };

        void addBuyOrder(int clientID, int quantity, int price) {
            buyOrders.push_back(Order(clientID, quantity, price, MyID, 0));
            MyID++;
            mergeOrders();
        }

        void addSellOrder(int clientID, int quantity, int price) {
            buyOrders.push_back(Order(clientID, quantity, price, MyID, 1));
            //sellOrders.push_back(Order(clientID, quantity, price, MyID));
            MyID ++;
            mergeOrders();
        }

        void removeBuyOrder(int ID) {
            auto it = std::remove_if(buyOrders.begin(), buyOrders.end(), [ID](const Order& order) {
                return order.ID == ID;
            });
            buyOrders.erase(it, buyOrders.end());
            mergeOrders();
        }
    
    void displayOrderBook() {
        std::cout << "Sort Merge List| TEST |\nAchat:\t\t\t\t\t\tVente:\n";
        displayOrders(achatList, venteList);
    }

    void displayOrdersDetails() {
        std::cout << "Order Detail\nAchat (details):\t\t\t\tVente (details):\n";
        displayOrdersDetails( buyOrders);
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
        if (buyOrders.empty() || achatList.empty() || venteList.empty()) {
            return;
        }

        for (int y = 0; y < achatList.size(); y ++) {
            if(venteList.empty())
                break;
           if (achatList[y].price >= venteList[0].price){
                if (achatList[y].quantity < venteList[0].quantity) {
                    // std::cout << "=== | achat < vente |===\n";
                    // std::cout << "ACHAT de : " <<  achatList[y].quantity << "\t au prix de " << venteList[0].price << " achat ID " << achatList[y].clientID << " vente ID: " << venteList[0].clientID <<"\n\n";
                    venteList[0].quantity -= achatList[y].quantity;
                    BuyInvoice(achatList[y].quantity , venteList[0].price);
                    SellInvoice(achatList[y].quantity , venteList[0].price);
                } else if (achatList[y].quantity == venteList[0].quantity) {
                    // std::cout << "=== | achat == vente |===\n";
                    // std::cout << "ACHAT de : " << achatList[y].quantity << "\t au prix de " << venteList[0].price << " achat ID " << achatList[y].clientID << " vente ID: " << venteList[0].ID  << "\n\n";
                    venteList[0].quantity -= achatList[y].quantity;
                    BuyInvoice(venteList[0].quantity, venteList[0].price);
                    SellInvoice(venteList[0].quantity, venteList[0].price);
                } else if (achatList[y].quantity > venteList[0].quantity) {
                    // std::cout << "=== | achat > vente |===\n";
                    // std::cout << "ACHAT de : " << venteList[0].quantity << "\t au prix de " << venteList[0].price << " achat ID " << achatList[y].clientID << " vente ID: " << venteList[0].ID << "\n\n";
                    // std::cout << "nb vente : " << venteList[0].quantity << " nb achat "<< achatList[y].quantity << " Result : " << (achatList[y].quantity - venteList[0].quantity) << "\n";
                    BuyInvoice(venteList[0].quantity, venteList[0].price);
                    SellInvoice(venteList[0].quantity, venteList[0].price);
                }
            }
        }
    } 

    private:
        int MyID = 0;
        std::vector<Order> buyOrders;

        std::vector<Order> achatList;
        std::vector<Order> venteList;

        void BuyInvoice(int dif, int cost){
        for (int size = 0; size < buyOrders.size(); size ++) {
            if (buyOrders[size].category == 0 && buyOrders[size].price >= cost){
                if(dif >= buyOrders[size].quantity){
                    std::cout << " Client ID " << buyOrders[size].clientID << " a acheter " << buyOrders[size].quantity << "\n";
                    dif -= buyOrders[size].quantity ;
                    removeBuyOrder(buyOrders[size].ID);
                }else{
                    std::cout << " Client ID " << buyOrders[size].clientID << " a acheter " << cost << "\n";
                    dif -=  buyOrders[size].quantity;
                    buyOrders[size].quantity -= dif;
                }
            }
            if(cost == 0)
                break;
        }
        //if(cost > 0)
        //    std::cout << "ERROR BUY INVOICE CALCUL :: "<< dif <<"\n";
    }

    void SellInvoice(int dif, int cost){
        for (int size = 0; size <  buyOrders.size(); size ++) {
            if (buyOrders[size].category == 1 && buyOrders[size].price <= cost){
                if(dif >= buyOrders[size].quantity){
                    std::cout << " Client ID " << buyOrders[size].clientID << " a vendu " << buyOrders[size].quantity << "\n";
                    dif -= buyOrders[size].quantity;
                    removeBuyOrder(buyOrders[size].ID);
                }else{
                    std::cout << " Client ID " << buyOrders[size].clientID << " a vendu " << cost << "\n";
                    dif -= buyOrders[size].quantity;
                    buyOrders[size].quantity -= dif;
                }
            }
            if(cost == 0)
                break;
        }
        // if(cost > 0)
        //     std::cout << "ERROR BUY INVOICE CALCUL :: "<< dif<<"\n";
    }

        void mergeOrders() {
            achatList.clear();
            venteList.clear();
    
            for (const auto& order : buyOrders) {
                bool merged = false;

                if(order.category == 0){
                    mergeAchat(order);
                }else{
                    mergeVente(order);
                }
            }

            std::sort(venteList.begin(), venteList.end(), [](const auto& a, const auto& b) -> bool {
                return a.price < b.price;
            });
            std::sort(achatList.begin(), achatList.end(), [](const auto& a, const auto& b) -> bool {
                return a.price > b.price;
            });
        }

        void mergeAchat(const Order& order) {
            bool merged = false;

            for (auto& row : achatList) {
                if (order.price == row.price) {
                    row.clientID++;
                    row.quantity += order.quantity;
                    merged = true;
                    break;
                }
            }

            if (!merged) {
                achatList.push_back(Order(1, order.quantity, order.price, 0, 0));
            }
        }

        void mergeVente(const Order& order) {
            bool merged = false;

            for (auto& row : venteList) {
                if (order.price == row.price) {
                    row.clientID++;
                    row.quantity += order.quantity;
                    merged = true;
                    break;
                }
            }

            if (!merged) {
                venteList.push_back(Order(1, order.quantity, order.price, 0, 0));
            }
        }

        void displayOrders(const std::vector<Order>& orderListAchat, const std::vector<Order>& orderListVente) {
            int count = 0;
            int maxSize = 30;

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

        void displayOrdersDetails(const std::vector<Order>& orderListAchat) {
        int count = 0;
        int maxSize = 30;

        for (int i = 0; i < maxSize; ++i) {
            if (i < orderListAchat.size()) {
                if(orderListAchat[i].category == 0){
                    std::cout << "Client ID  (achat)"  << orderListAchat[i].clientID << ", Quantite: " << orderListAchat[i].quantity << ", Prix: " << orderListAchat[i].price << ", OrderID: "<< orderListAchat[i].ID;    
                } else {
                    std::cout << "Client ID  (vente)"  << orderListAchat[i].clientID << ", Quantite: " << orderListAchat[i].quantity << ", Prix: " << orderListAchat[i].price << ", OrderID: "<< orderListAchat[i].ID;
                }
                std::cout << "\t\t\t";
            }
            std::cout << "\n";
            count++;
            if (i >= orderListAchat.size()) {
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
    orderBook.addBuyOrder(2, 10, 92);
    orderBook.addBuyOrder(2, 10, 81);
    orderBook.addSellOrder(4, 7, 105);
    orderBook.addSellOrder(4, 7, 105);
    orderBook.addSellOrder(5, 12, 98);
    orderBook.addSellOrder(6, 6, 105);
    orderBook.addSellOrder(5, 12, 93);
    orderBook.addSellOrder(5, 12, 70);
    orderBook.addSellOrder(4, 30, 15);
    orderBook.addSellOrder(5, 12, 100);
    orderBook.addSellOrder(6, 6, 10);
    orderBook.addBuyOrder(1, 30, 60);
    orderBook.addBuyOrder(2, 10, 95);
    orderBook.addBuyOrder(3, 8, 150);
    //orderBook.displayOrdersDetails();

    std::cout << "\n_______| ORDER BOOK |_________\n";
    orderBook.displayOrderBook();
    orderBook.removeBuyOrder(14);
    //std::cout << "_______________________________________________________________\n";
    //orderBook.displayOrdersDetails();
    std::cout << "''''''''''''''''''''''''''''''| id 2 |''''''''''''''''''''''''''''''''''''\n";
    orderBook.displayClient(2);
    std::cout << "___________________________|MANAGE MARCKET|____________________________________\n";
    orderBook.manageSellMarcket();
    //std::cout << "______________________________[DYSPALY MANAGE MARCKET]_________________________________\n";
    std::cout << "\n_______| ORDER BOOK |_________\n";
    //orderBook.displayOrderBook();
    return 0;
}