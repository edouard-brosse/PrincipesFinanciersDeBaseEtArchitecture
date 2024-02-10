#include <iostream>
#include <vector>
#include <string>

class FIXField {
private:
    int tag;
    std::string value;
public:
    FIXField(int tag, const std::string& value) : tag(tag), value(value) {}

    int getTag() const { return tag; }
    std::string getValue() const { return value; }
};


class FIXMessage {

    protected:
        std::vector<FIXField> fields;
        std::string Header;
        std::string Boddies;
        std::string trailer;
        std::string FullString;

        void headerMaker(std::string msg);
        void BodyMaker(std::string msg);

    public:
        void fixMaker(std::string msg);

};