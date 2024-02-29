#ifndef TRAILLER_H
#define TRAILLER_H

#include <string>


class Trailler {
private:
    std::string traillerCalculated(std::string body);
public:
    std::string TraillerMaker(std::string body);
};
#endif