#include <vector>
#include <string>
#include <iostream>
#include <sstream> 

class FixParser {
private:
    std::vector<std::string> Header;
    std::vector<std::string> Body;
    std::string Final;

    void headerMaker(std::string msg);
    void BodyMaker(std::string msg);

public:
    void fixMaker(std::string msg);
};

void FixParser::headerMaker(std::string msg) {
    std::string HeaderFinal = "";
    int FixSize = 0;
    Header.push_back("8=FIX.4.2^"); // Version de FIX
    Header.push_back("9="); // Longueur du corps
    //FixSize = Final.length();
    Header.push_back(std::to_string(Final.length()) + "^"); // Convert FixSize to string
    Header.push_back("35=" + msg); // Integer message Sequence Number
    //Header.push_back("^");
    //  8 |Version de FIX
    //  9 |Longueur du corps
    //  35 |Type de message
    //  49 |ID de l'envoyeur
    //  56 |ID du receveur
    //  34 |Numero de la requette
    //  52 |Heure d'envoie

    //type ici 
     
    for(int i = 0; i < Header.size(); i++){
        HeaderFinal.append(Header[i]);
        std::cout << Header[i] << "\n";
    }
    std::cout << "header final " << HeaderFinal  << "\n";
   Final = HeaderFinal + "|" + Final;
   //std::string temp;
   //temp.append(HeaderFinal);
   //temp.append(Final);
   //Final = temp;
   std::cout << Final << "\n";
}

void FixParser::BodyMaker(std::string msg) {
    std::string msgType = "";
    //  226 |ID de la personne
    //  40 |type de requette
    //  264 |ID de la requette ou non si pas encore d'id
    //  14 |quantitée a acheter/ vendre / modifier
    //  44 |prix
    std::vector<std::string> bodyPart;
    std::string temp;
    std::istringstream iss(msg); // Create istringstream object
    while (std::getline(iss, temp, ' ')) // Use istringstream object instead of msg
    {
        bodyPart.push_back(temp);
    }
    for(int i = 0; i < bodyPart.size(); i++) {
        std::cout << bodyPart[i] << std::endl;
    }
    if(bodyPart[0] == "addOrder") {
            std::cout << "addOrder" << std::endl;
            Body.push_back("40=0"); // type de requette
            Body.push_back("14=" + bodyPart[2]); // quantitée
            Body.push_back("44=" + bodyPart[1]); // prix
        }
        else if(bodyPart[0] == "modifyOrder") {
            std::cout << "modifyOrder" << std::endl;
            Body.push_back("40=1"); // type de requette
            Body.push_back("44=" + bodyPart[1]); // prix
            Body.push_back("14=" + bodyPart[2]); // quantitée
        }
        else if(bodyPart[0] == "cancelOrder") {
            std::cout << "cancelOrder" << std::endl;
            Body.push_back("40=2"); // type de requette
        }else if(bodyPart[0] == "displayOrder") {
            std::cout << "displayOrder" << std::endl;
            Body.push_back("40=3"); // type de requette
        }
        else {
            std::cout << "Error" << std::endl;
        }
    for(int i = 0; i < Body.size(); i++) {
        std::cout << Body[i] << std::endl;
        Final.append("^");
        Final.append(Body[i]);
    }
    std::cout << Final << std::endl;
    headerMaker(msgType);
}

void FixParser::fixMaker(std::string msg) {
    BodyMaker(msg);
    // Code de la fonction fixMaker
}

int main() {
    FixParser fixParser;
    fixParser.fixMaker("addOrder 20 10");
    return 0;
}