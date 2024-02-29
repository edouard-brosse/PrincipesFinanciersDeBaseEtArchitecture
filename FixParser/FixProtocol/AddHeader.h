#ifndef ADDHEADER_H
#define ADDHEADER_H
#include <string>
#include "LibData.h"


class AddHeader: public LibData{
public:
    std::string HeaderMaker(std::string body, std::string MsgType, std::string RqtNbn, std::string Sender, std::string Target);
};

#endif