#ifndef FIXPROTOCOL_H
#define FIXPROTOCOL_H

#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <unordered_map>
#include <sstream>

class LibData {
public:
    std::string GetTime();
};

class AddHeader: public LibData{
public:
    std::string HeaderMaker(std::string body, std::string MsgType, std::string RqtNbn, std::string Sender, std::string Target);
};

class Trailler {
public:
    std::string TraillerMaker(std::string body);
private:
    std::string traillerCalculated(std::string body);
};

class AddOrder: public LibData{
private:
    int clOrdID = 0;
public:
    std::string addOrder(const std::string price, const std::string qty, std::string Sender, std::string Target);
};

class AddOrderSell: public LibData{
private:
    int clOrdID = 0;
public:
    std::string SellOrder(const std::string price, const std::string qty, std::string Sender, std::string Target);
};

class UpdateOrder: public AddHeader, public Trailler{
public:
    std::string UpdateOrd(const std::string clOrdID, std::string price,  std::string qty, std::string Sender, std::string Target, std::string OrderId, std::string NewID, std::string OrderType);
};

class OrderCancel:  public AddHeader, public Trailler{
public:
    std::string CancelOrd(const std::string clOrdID, std::string Sender, std::string Target, std::string OrderId, std::string OrderType);
};

class ExReport: public AddHeader, public Trailler{
public:
    std::string ExecutionReport( std::string Sender, std::string Target, std::string OrderType, std::string ExecType, std::string OrdStatus, std::string nb, std::string prixMoyen, std::string ExID);
};

class LogOn: public AddHeader, public Trailler{
public:
    std::string logOn( std::string Sender, std::string Target);
};

#endif // FIXPROTOCOL_H