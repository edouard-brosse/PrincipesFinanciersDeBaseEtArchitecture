#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure pour représenter un ordre
struct Order {
    int clientId;
    char type;  // 'A' pour Achat, 'V' pour Vente
    int quantity;
    double price;
};

// Fonction pour ajouter un ordre
void addOrder(vector<Order>& buyOrders, vector<Order>& sellOrders, const Order& order) {
    if (order.type == 'A') {
        buyOrders.push_back(order);
    } else if (order.type == 'V') {
        sellOrders.push_back(order);
    }
}

// Fonction pour afficher les ordres
void listOrders(const vector<Order>& orders) {
    for (const auto& order : orders) {
        cout << "ID client: " << order.clientId << ", Type: " << (order.type == 'A' ? "Achat" : "Vente")
             << ", Quantité: " << order.quantity << ", Prix: " << order.price << endl;
    }
}

// Fonction pour annuler un ordre
void cancelOrder(vector<Order>& orders, int clientId) {
    orders.erase(remove_if(orders.begin(), orders.end(), [clientId](const Order& order) {
        return order.clientId == clientId;
    }), orders.end());
}

// Fonction pour trier les ordres par prix (du plus bas au plus haut)
void sortOrdersByPrice(vector<Order>& orders) {
    sort(orders.begin(), orders.end(), [](const Order& a, const Order& b) {
        return a.price < b.price;
    });
}

int main() {
    vector<Order> buyOrders;  // Tableau d'achats
    vector<Order> sellOrders; // Tableau de ventes

    string command;

    while (true) {
        cout << "Entrez une commande (exit pour quitter, help pour l'aide): ";
        cin >> command;

        if (command == "exit") {
            break;
        } else if (command == "add") {
            Order order;
            cin >> order.clientId >> order.type >> order.quantity >> order.price;
            addOrder(buyOrders, sellOrders, order);
        } else if (command == "list") {
            string orderType;
            cin >> orderType;
            if (orderType == "Achat") {
                listOrders(buyOrders);
            } else if (orderType == "Vente") {
                listOrders(sellOrders);
            }
        } else if (command == "cancel") {
            int clientId;
            cin >> clientId;
            cancelOrder(buyOrders, clientId);
            cancelOrder(sellOrders, clientId);
        } else if (command == "help") {
            cout << "Commandes disponibles:" << endl;
            cout << "add: Ajouter un ordre (IDClient Type(A/V) Quantité Prix)" << endl;
            cout << "list Achat/Vente: Afficher les ordres d'achat ou de vente" << endl;
            cout << "cancel IDClient: Annuler un ordre" << endl;
            cout << "exit: Quitter le programme" << endl;
        } else {
            cout << "Commande non reconnue. Tapez 'help' pour voir la liste des commandes." << endl;
        }
    }

    return 0;
}
