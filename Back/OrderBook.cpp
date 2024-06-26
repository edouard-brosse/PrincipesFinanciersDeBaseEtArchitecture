#include "OrderBook.h"

void OrderBook::addBuyOrder(int clientID, int quantity, int price) {
            buyOrders.push_back(Order(clientID, quantity, price, MyID, 0));
            MyID++;
            mergeOrders();
        }

void OrderBook::addSellOrder(int clientID, int quantity, int price) {
            buyOrders.push_back(Order(clientID, quantity, price, MyID, 1));
            //sellOrders.push_back(Order(clientID, quantity, price, MyID));
            MyID ++;
            mergeOrders();
        }

void OrderBook::removeBuyOrder(int ID) {
            auto it = std::remove_if(buyOrders.begin(), buyOrders.end(), [ID](const Order& order) {
                return order.ID == ID;
            });
            buyOrders.erase(it, buyOrders.end());
            mergeOrders();
        } 
    
void OrderBook::displayOrderBook() {
    std::cout << "Sort Merge List| TEST |\nAchat:\t\t\t\t\t\tVente:\n";
    displayOrders(achatList, venteList);
}

void OrderBook::displayOrdersDetails() {
    std::cout << "Order Detail\nAchat (details):\t\t\t\tVente (details):\n";
    displayOrdersDetails( buyOrders);
}

void OrderBook::displayClient(int cliId) {
    std::cout << "Ordres d'achat pour le client ID " << cliId << " :\n";
    for (const auto& order : buyOrders) {
        if (order.clientID == cliId) {
            std::cout << "Client ID : " << order.clientID << " Category: " << order.category << ", Quantite: " << order.quantity << ", Prix: " << order.price << ", OrderID: " << order.ID << "\n";
        }
        else {
            std::cout << "OTHER" << order.clientID << " Category: " << order.category <<" Quantite: " << order.quantity << " price " << order.price << " OrderID: " << order.ID << "\n";
        }
    }
}

void OrderBook::manageSellMarcket() {
    mergeOrders();
    if (buyOrders.empty() || achatList.empty() || venteList.empty()) {
        return;
    }
    for (int y = 0; y < achatList.size(); y ++) {
        if(venteList.empty())
            break;
        //std::cout << "---------| Tour |------------\n";
        // std::cout << "------| manage sell |----------\n";
     //displayOrderBook();
        //std::cout << "Achat: " << achatList[y].price << " Vente: " << venteList[0].price << "\n";
       if (achatList[y].price >= venteList[0].price){
       //   std::cout << "RENTRE COND Achat: " << achatList[y].price << " Vente: " << venteList[0].price << "\n";
          BuyCallcul(this);
          manageSellMarcket();
        }
    }
    // std::cout << "------| manage sell |----------\n";
    // displayOrderBook();
} 

void OrderBook::BuyCallcul(OrderBook *orderBook){
    int disponible = venteList[0].quantity;
    for (int i = 0; i < buyOrders.size(); i++){
        if(disponible < 1)
            break;
        if(buyOrders[i].price >= venteList[0].price && buyOrders[i].category == 0){
            if(buyOrders[i].quantity > disponible) {
                std::cout << "Client ID" << buyOrders[i].clientID << " a acheter: " << disponible << " au prix de: " << venteList[0].price << "\n";
                //std::cout << "disponible : " << disponible << "\n";
                buyOrders[i].quantity -= disponible;
                SellCalcul( disponible, venteList[0].price);
                //std::cout << "== Order detail ==\n";
                //displayOrdersDetails();
                disponible = 0;
                break;
            } else {
                std::cout << "Client ID" << buyOrders[i].clientID << " a acheter: " << buyOrders[i].quantity << " au prix de: " << venteList[0].price << "\n";
                disponible =  buyOrders[i].quantity;
                removeBuyOrder(buyOrders[i].ID);
                SellCalcul(disponible, venteList[0].price);
            }
        }
    }
}

void OrderBook::SellCalcul(int sell, int cost){
    for (int i = 0 ; i < buyOrders.size(); i++){
        if(sell < 1)
            break;
        //std::cout << "Sell: " << sell << " Cost: " << cost << " Price: " << buyOrders[i].price << " Category: " << buyOrders[i].category << "\n";
        if(buyOrders[i].price <= cost && buyOrders[i].category == 1){
            if(buyOrders[i].quantity > sell) {
                std::cout << "Client ID" << buyOrders[i].clientID << " a vendu: " << sell << " au prix de: " << cost << "\n";
                buyOrders[i].quantity -= sell;
                break;
            } else {
                std::cout << "Client ID" << buyOrders[i].clientID << " a vendu: " << sell << " au prix de: " << cost << "\n";
                sell -= buyOrders[i].quantity;
                //std::cout << "Client ID (Vente 2): " << buyOrders[i].clientID << ", Quantite: " << buyOrders[i].quantity << ", Prix: " << buyOrders[i].price << ", OrderID: " << buyOrders[i].ID << "\n" <<
                //"a Vendu :" << buyOrders[i].quantity << "\n";
                removeBuyOrder(buyOrders[i].ID);
                SellCalcul(sell, cost);
            }
        }
    }
    manageSellMarcket();
}

void OrderBook::mergeOrders() {
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
        std::cout << "trie achat\n";
    });
}

void OrderBook::mergeAchat(const Order& order) {
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

void OrderBook::mergeVente(const Order& order) {
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

void OrderBook::displayOrders(const std::vector<Order>& orderListAchat, const std::vector<Order>& orderListVente) {
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

void OrderBook::UpdateOrder(int ID, int quantity, int price) {
    for (int i = 0; i < buyOrders.size(); i++) {
        if (buyOrders[i].ID == ID) {
            buyOrders[i].quantity = quantity;
            buyOrders[i].price = price;
            mergeOrders();
            break;
        }
    }
}

void OrderBook::displayOrdersDetails(const std::vector<Order>& orderListAchat) {
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

