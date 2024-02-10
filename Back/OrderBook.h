#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include <iostream>
#include <vector>
#include <algorithm>

class OrderBook{
    public:
        struct Order {
            int clientID; // l'ID du client
            int quantity;  // la quantité d'actions à acheter ou vendre
            int price; // le prix voulu auquel acheter ou vendre
            int ID; // Unique ID, ID of the order
            int category; // 0 pour achat, 1 pour vente
            Order(int id, int qty, int prc, int myID, int Category) : clientID(id), quantity(qty), price(prc), ID(myID), category(Category) {}
        };

        void addBuyOrder(int clientID, int quantity, int price);
        void addSellOrder(int clientID, int quantity, int price);
        void removeBuyOrder(int ID);
        void displayOrderBook();
        void displayOrdersDetails();
        void displayClient(int cliId);
        void manageSellMarcket(); // a deplacer pour otomatiser quand on ajoute un order
        void UpdateOrder(int ID, int quantity, int price);

    private:
        int MyID = 0;
        std::vector<Order> buyOrders;

        std::vector<Order> achatList;
        std::vector<Order> venteList;

        void mergeOrders();
        void mergeAchat(const Order& order);
        void mergeVente(const Order& order);
        void displayOrders(const std::vector<Order>& orderListAchat, const std::vector<Order>& orderListVente);
        void displayOrdersDetails(const std::vector<Order>& orderListAchat);
        void BuyCallcul();
        void SellCalcul(int sell, int cost);
};

#endif