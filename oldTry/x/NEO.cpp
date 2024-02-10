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
        std::cout << "======================== |PASSE |===============\n";

        for (int y = 0; y < achatList.size(); y ++) {
            if(venteList.empty())
                break;
           if (achatList[y].price >= venteList[0].price){
                if (achatList[y].quantity < venteList[0].quantity) {
                    std::cout << "=== | achat < vente |===\n";
                    std::cout << "ACHAT de : " <<  achatList[y].quantity << "\t au prix de " << venteList[0].price << " achat ID " << achatList[y].clientID << " vente ID: " << venteList[0].clientID <<"\n\n";
                    //venteList[0].quantity -= achatList[y].quantity;
                    BuyInvoice(achatList[y].quantity , venteList[0].price);
                    SellInvoice(achatList[y].quantity , venteList[0].price);
                } else if (achatList[y].quantity == venteList[0].quantity) {
                    std::cout << "=== | achat == vente |===\n";
                    std::cout << "ACHAT de : " << achatList[y].quantity << "\t au prix de " << venteList[0].price << " achat ID " << achatList[y].clientID << " vente ID: " << venteList[0].ID  << "\n\n";
                    //venteList[0].quantity -= achatList[y].quantity;
                    BuyInvoice(venteList[0].quantity, venteList[0].price);
                    SellInvoice(venteList[0].quantity, venteList[0].price);
                } else if (achatList[y].quantity > venteList[0].quantity) {
                    std::cout << "=== | achat > vente |===\n";
                    std::cout << "ACHAT de : " << venteList[0].quantity << "\t au prix de " << venteList[0].price << " achat ID " << achatList[y].clientID << " vente ID: " << venteList[0].ID << "\n\n";
                    std::cout << "nb vente : " << venteList[0].quantity << " nb achat "<< achatList[y].quantity << " Result : " << (achatList[y].quantity - venteList[0].quantity) << "\n";
                    BuyInvoice(venteList[0].quantity, venteList[0].price);
                    SellInvoice(venteList[0].quantity, venteList[0].price);
                }
            }
        }
    } 

    
    void BuyInvoice(int dif, int cost){
        std::cout << "---|buy INVOICE "<< dif << "|---\n";
        for (int size = 0; size < buyOrders.size(); size ++) {
            if (buyOrders[size].category == 0 && buyOrders[size].price >= cost){
                if(dif >= buyOrders[size].quantity){
                    std::cout << " Client ID " << buyOrders[size].clientID << " a acheter " << buyOrders[size].quantity << "\n";
                    std::cout << "sdif :: " << buyOrders[size].quantity - dif<< " dif: " << dif << " buyOrder quantity: " << buyOrders[size].quantity << "\n";
                    //dif = buyOrders[size].quantity - dif;
                    dif -= buyOrders[size].quantity;
                    std::cout << "dif 1 : " << dif << "\n";
                    removeBuyOrder(buyOrders[size].ID);
                }else{
                    std::cout << " Client ID " << buyOrders[size].clientID << " a acheter " << cost << "\n";
                    std::cout << "sdif :: " << dif - buyOrders[size].quantity << "\n";
                    dif -=  buyOrders[size].quantity;
                    std::cout << "dif 2 : " << dif << "\n";
                    // buyOrders[size].quantity -= size;
                    buyOrders[size].quantity -= size;

                }
            } else {
                if(buyOrders[size].price == cost){
                    std::cout << "FInal Error cost :: " << cost << " buyOrderSize: " << buyOrders[size].price << "\n";
                    std::cout << "ICI ERROR PASSE  Category :: " << buyOrders[size].category <<"\n";
                }
            }
            //if(cost == 0){
            if(dif <= 0){
                std::cout << " Buy Exit ";
                break;
                }
        }
        if(cost > 0)
            std::cout << "ERROR BUY INVOICE CALCUL " << cost <<"\n";
    }

    void SellInvoice(int dif, int cost){
        std::cout << "---|SELL INVOICE " << dif << "  cost: "<< cost << "|---\n";
        //std::cout << "size: " << buyOrders.size() << " buyOrder:\n";
        for (int size = 0; size < buyOrders.size(); size ++) {
            //std::cout << " SELL TOUR";
            if (buyOrders[size].category == 1 && buyOrders[size].price <= cost){
                if(dif >= buyOrders[size].quantity){
                    std::cout << " Client ID " << buyOrders[size].clientID << " a vendu " << buyOrders[size].quantity << "\n";
                    dif = buyOrders[size].quantity - dif;
                    removeBuyOrder(buyOrders[size].ID);
                }else{
                    std::cout << " Client ID " << buyOrders[size].clientID << " a vendu " << cost << "\n";
                    dif = cost - buyOrders[size].quantity;
                    std::cout << "cost call :: " << cost - buyOrders[size].quantity << "\n";
                    buyOrders[size].quantity -= size;
                }
            }
            //std::cout << " ----- cost = " << cost << " -----\n";
            // if(cost <= 0)
            if(dif <= 0)
                break;
        }
        //if(cost > 0)
        //    std::cout << "ERROR SELL INVOICE CALCUL " << dif <<"\n";
    }

    private:
        int MyID = 0;
        std::vector<Order> buyOrders;

        std::vector<Order> achatList;
        std::vector<Order> venteList;

        void mergeOrders() {
            achatList.clear();
            venteList.clear();
    
            //std::cout << "-------------------| NEW TOUR |-----------------\n";
            for (const auto& order : buyOrders) {
                bool merged = false;

                if(order.category == 0){
                    //std::cout << "achat ||order id" << order.ID << " categorie: " << order.category << "\n";
                    mergeAchat(order);
                }else{
                    //std::cout << "vente ||order id" << order.ID << " categorie: " << order.category << "\n";
                    mergeVente(order);
                }
            }
            std::sort(venteList.begin(), venteList.end(), [](const auto& a, const auto& b) -> bool {
                return a.price < b.price;
            });
            std::cout << "UPDATE Sale SORT\n" ;
            std::sort(achatList.begin(), achatList.end(), [](const auto& a, const auto& b) -> bool {
                return a.price > b.price;
            });
            std::cout << "UPDATE SORT\n" ;
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

        void displayOrdersDetails(const std::vector<Order>& orderListAchat) {
        int count = 0;
        int maxSize = 10;

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
    //orderBook.addBuyOrder(1, 5, 1000);
    orderBook.addBuyOrder(1, 5, 100);
    orderBook.addBuyOrder(2, 10, 95);
    orderBook.addBuyOrder(3, 8, 100);
    orderBook.addBuyOrder(7, 3, 100);
    // std::cout << "_______| ManageSellMarcket |_________\n";
    // orderBook.manageSellMarcket();
    // orderBook.displayOrdersDetails();
    // std::cout << "_______| 2 |_________\n";
    orderBook.addBuyOrder(1, 30, 60);
    orderBook.addSellOrder(4, 7, 105);
    orderBook.addSellOrder(5, 12, 98);
    orderBook.addSellOrder(9, 2, 98);
    orderBook.addSellOrder(6, 6, 105);

    orderBook.displayOrdersDetails();
    std::cout << "\n_______| ORDER BOOK |_________\n";
    orderBook.displayOrderBook();
    //std::cout << "\n_______| ManageSellMarcket |_________\n";
    //orderBook.manageSellMarcket();
    //std::cout << "\n_______| 2 |_________\n";
    //orderBook.displayOrdersDetails();
    //orderBook.displayOrdersDetails();
    // Affichage des 10 premières lignes du carnet d'ordres
    //std::cout << "\n_______| ORDER BOOK |_________\n";
    //orderBook.displayOrderBook();

    // orderBook.addSellOrder(4, 30, 15);
    // orderBook.addSellOrder(5, 12, 100);
    // orderBook.addSellOrder(6, 6, 10);
     //orderBook.addBuyOrder(1, 30, 60);
    // orderBook.addBuyOrder(2, 10, 95);
    // orderBook.addBuyOrder(3, 8, 150);
    // //std::cancelOrder(14);
    // std::cout << "_______________________________________________________________\n";
    // orderBook.displayOrdersDetails();
    // std::cout << "''''''''''''''''''''''''''''''| id 2 |''''''''''''''''''''''''''''''''''''\n";
    orderBook.displayClient(2);
    std::cout << "___________________________|MANAGE MARCKET|____________________________________\n";
    orderBook.manageSellMarcket();
    std::cout << "______________________________[DYSPALY MANAGE MARCKET]_________________________________\n";
    std::cout << "\n_______| ORDER BOOK |_________\n";
    orderBook.displayOrderBook();
    return 0;
}