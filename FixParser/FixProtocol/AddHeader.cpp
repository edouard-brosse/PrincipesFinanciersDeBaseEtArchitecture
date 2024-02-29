#include "AddHeader.h"

std::string AddHeader::HeaderMaker(std::string body, std::string MsgType, std::string RqtNbn, std::string Sender, std::string Target) {
        std::string header = "";
        
        header.append("8=FIX.4.2^");
        header.append("9=" );
        header.append(std::to_string(body.length()));
        header.append("^35=" );
        header.append(MsgType);
        header.append("^49="); // You need to specify sender and target comp ids
        header.append(Sender); 
        header.append("^56="); // Or adjust accordingly
        header.append(Target);
        header.append("^34="  );
        header.append(RqtNbn);
        //header.append("^52=" + std::to_string(now->tm_hour) + ":" + std::to_string(now->tm_min) + ":" + std::to_string(now->tm_sec) + "^");
        header.append("^52=");
        header.append(GetTime());
        header.append("^");
        return header;
    }