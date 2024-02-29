#ifndef ADDORDER_H
#define ADDORDER_H

#include "LibData.h"
#include <string>
class AddOrder: public LibData{
public:

    void addOrder(const std::string clOrdID, const std::string price, const std::string qty, std::string Sender, std::string Target);
};

#endif