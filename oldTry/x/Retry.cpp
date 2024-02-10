#include <iostream>
#include <vector>
#include <algorithm>

//ORDER BOOK
class OrderBook {
    public:
        struct Order {
            int clientID; // l'ID du client
            int quantity;  // la quantité d'actions à acheter ou vendre
            int price; // le prix voulu auquel acheter ou vendre
            int ID; // Unique ID, ID of the order
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
        mergeOrders();
        if (buyOrders.empty() || achatList.empty() || venteList.empty()) {
            return;
        }
        std::cout << "======================== |Manage Marcket |===============\n";

        for (int y = 0; y < achatList.size(); y ++) {
            if(venteList.empty())
                break;
           if (achatList[y].price >= venteList[0].price){
              BuyCallcul();
              manageSellMarcket();
            }
        }
    } 

    void BuyCallcul(){
        int disponible = venteList[0].quantity;
        std::cout << "======================== |Buy Calcul |===============\n";
        for (int i = 0; i < buyOrders.size(); i++){
            if(disponible < 1)
                break;
            if(buyOrders[i].price >= venteList[0].price && buyOrders[i].category == 0){
                if(buyOrders[i].quantity > disponible) {
                    std::cout << "Client ID (Achat 1): " << buyOrders[i].clientID << ", Quantite: " << buyOrders[i].quantity << ", Prix: " << buyOrders[i].price << ", OrderID: " << buyOrders[i].ID << "\n" <<
                    "a acheter :" << disponible << " sell:: " << disponible <<"\n";
                    SellCalcul( disponible, venteList[0].price);
                    buyOrders[i].quantity -= disponible;
                    disponible = buyOrders[i].quantity -= disponible;
                    
                    break;
                } else {
                    //disponible -= buyOrders[i].quantity;
                    std::cout << "Client ID (Achat 2): " << buyOrders[i].clientID << ", Quantite: " << buyOrders[i].quantity << ", Prix: " << buyOrders[i].price << ", OrderID: " << buyOrders[i].ID << "\n" <<
                    "a acheter :" << buyOrders[i].quantity << " sell:: " <<buyOrders[i].quantity << "\n";
                    disponible =  buyOrders[i].quantity;
                    removeBuyOrder(buyOrders[i].ID);
                    SellCalcul(disponible, venteList[0].price);
                }

            }
        }
    }

    void SellCalcul(int sell, int cost){
        std::cout << "======================== |Sell Calcul |===============\n";
        for (int i = 0 ; i < buyOrders.size(); i++){
            if(buyOrders[i].price <= cost && buyOrders[i].category == 1){
               // std::cout << "Client ID (Vente 1): " << buyOrders[i].clientID << ", Quantite: " << buyOrders[i].quantity << ", Prix: " << buyOrders[i].price << ", OrderID: " << buyOrders[i].ID << " cost :: " <<  cost <<"\n" ;
                if(buyOrders[i].quantity > sell) {
                    std::cout << "Client ID (Vente 1): " << buyOrders[i].clientID << ", Quantite: " << buyOrders[i].quantity << ", Prix: " << buyOrders[i].price << ", OrderID: " << buyOrders[i].ID << "\n" <<
                    "a vendu :" << sell << "\n";
                    buyOrders[i].quantity -= sell;
                    break;
                } else {
                    sell -= buyOrders[i].quantity;
                    std::cout << "Client ID (Vente 2): " << buyOrders[i].clientID << ", Quantite: " << buyOrders[i].quantity << ", Prix: " << buyOrders[i].price << ", OrderID: " << buyOrders[i].ID << "\n" <<
                    "a Vendu :" << buyOrders[i].quantity << "\n";
                    removeBuyOrder(buyOrders[i].ID);
                    SellCalcul(sell, cost);
                }
            }
        }
        manageSellMarcket();
    }

    private:
        int MyID = 0;
        std::vector<Order> buyOrders;

        std::vector<Order> achatList;
        std::vector<Order> venteList;

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
    orderBook.addBuyOrder(7, 1, 98);
    orderBook.addBuyOrder(3, 8, 100);
    orderBook.addBuyOrder(7, 3, 100);
    orderBook.addBuyOrder(1, 30, 60);
    orderBook.addSellOrder(4, 7, 105);
    orderBook.addSellOrder(5, 12, 98);
    orderBook.addSellOrder(9, 2, 98);
    orderBook.addSellOrder(6, 6, 105);

    orderBook.displayOrdersDetails();
    std::cout << "\n_______| ORDER BOOK |_________\n";
    orderBook.displayOrderBook();
    //orderBook.displayClient(2);
    std::cout << "___________________________|MANAGE MARCKET|____________________________________\n";
    orderBook.manageSellMarcket();
    std::cout << "______________________________[DYSPALY MANAGE MARCKET]_________________________________\n";
    std::cout << "\n_______| ORDER BOOK |_________\n";
    orderBook.displayOrderBook();
    return 0;
}