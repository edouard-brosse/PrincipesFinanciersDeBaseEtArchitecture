#include <iostream>
#include <vector>
#include <algorithm>

class Order {
public:
    Order(int id, int quantity, double price) : id(id), quantity(quantity), price(price) {}

    int getId() const { return id; }
    int getQuantity() const { return quantity; }
    double getPrice() const { return price; }

    void setQuantity(int newQuantity) { quantity = newQuantity; }

private:
    int id;
    int quantity;
    double price;
};

class OrderBook {
public:
    // Ajout d'un ordre
    void addOrder(const Order& order) {
        orders.push_back(order);
    }

    // Modification d'ordre
    void modifyOrder(int orderId, int newQuantity) {
        auto it = findOrderById(orderId);
        if (it != orders.end()) {
            it->setQuantity(newQuantity);
        }
    }

    // Annulation d'ordre
    void cancelOrder(int orderId) {
        orders.erase(std::remove_if(orders.begin(), orders.end(),
            [orderId](const Order& order) { return order.getId() == orderId; }),
            orders.end());
    }

    // Exécution totale
    void executeOrder(int orderId) {
        auto it = findOrderById(orderId);
        if (it != orders.end()) {
            std::cout << "Order " << orderId << " executed in full." << std::endl;
            orders.erase(it);
        }
    }

    // Exécution partielle
    void executePartialOrder(int orderId, int executedQuantity) {
        auto it = findOrderById(orderId);
        if (it != orders.end()) {
            if (executedQuantity < it->getQuantity()) {
                it->setQuantity(it->getQuantity() - executedQuantity);
                std::cout << "Order " << orderId << " executed partially with quantity " << executedQuantity << std::endl;
            } else {
                std::cout << "Order " << orderId << " executed in full." << std::endl;
                orders.erase(it);
            }
        }
    }

private:
    // Méthode utilitaire pour trouver un ordre par son ID
    std::vector<Order>::iterator findOrderById(int orderId) {
        return std::find_if(orders.begin(), orders.end(),
            [orderId](const Order& order) { return order.getId() == orderId; });
    }

    std::vector<Order> orders;
};

// Tests unitaires
int main() {
    OrderBook orderBook;

    Order order1(1, 10, 50.0);
    Order order2(2, 5, 48.0);

    orderBook.addOrder(order1);
    orderBook.addOrder(order2);

    orderBook.modifyOrder(1, 15);
    orderBook.cancelOrder(2);

    orderBook.executeOrder(1);
    orderBook.executePartialOrder(1, 8);

    return 0;
}
