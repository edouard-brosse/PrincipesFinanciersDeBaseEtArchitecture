#include "OrderBook.h"

int main() {
    OrderBook orderBook;
    orderBook.addBuyOrder(1, 5, 1000);
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
    std::cout << "___________________________|Client 1|____________________________________\n";
    orderBook.displayClient(1);
    //orderBook.UpdateOrder(5, 20, 200);
    //std::cout << "___________________________|Client 1|____________________________________\n";
    //orderBook.displayClient(1);
   // orderBook.displayOrderBook();
    //std::cout << "___________________________|Client 1|____________________________________\n";
    //orderBook.removeBuyOrder(5);
    //orderBook.displayClient(1);
    return 0;
}


/*
 vente 1 prix 100
 
 98  3


*/