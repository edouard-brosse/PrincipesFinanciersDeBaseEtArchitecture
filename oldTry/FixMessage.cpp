#include "FixMessage.h"

FixMessage::SpiltMsg(std::string msg)
{
    std::cout << "Split Message\n";
    std::cout << msg << "\n";
    std::string delimiter = "^";
    size_t pos = 0;
    std::string token;
    while ((pos = msg.find(delimiter)) != std::string::npos) {
        token = msg.substr(0, pos);
        std::cout << token << std::endl;
        msg.erase(0, pos + delimiter.length());
    }
    std::cout << msg << std::endl;
}