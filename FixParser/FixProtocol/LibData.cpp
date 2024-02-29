#include "LibData.h"

std::string LibData::GetTime() {
        std::time_t currentTime = std::time(nullptr);
        std::tm* now = std::localtime(&currentTime);
        std::stringstream ss;
        ss << std::put_time(now, "%y%m%d-%H:%M:%S");
        
        std::string dateTimeStr = ss.str();

        return dateTimeStr;
    }