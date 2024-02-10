#include <iostream>
#include <map>
#include <sstream>

// Fonction pour encoder un message FIX
std::string encodeFIXMessage(const std::map<int, std::string>& fields) {
    std::ostringstream oss;
    for (const auto& field : fields) {
        oss << field.first << "=" << field.second << "|";
    }
    return oss.str();
}

// Fonction pour décoder un message FIX
std::map<int, std::string> decodeFIXMessage(const std::string& message) {
    std::map<int, std::string> fields;
    std::istringstream iss(message);
    std::string field;
    while (std::getline(iss, field, '|')) {
        std::istringstream fieldStream(field);
        std::string tag, value;
        std::getline(fieldStream, tag, '=');
        std::getline(fieldStream, value);
        fields[std::stoi(tag)] = value;
    }
    return fields;
}

int main() {
    // Exemple d'encodage et de décodage
    std::map<int, std::string> sampleMessage = {
        {8, "FIX.4.4"},
        {35, "D"},
        {55, "AAPL"},
        {54, "1"},
        {38, "100"},
        {44, "50.00"}
    };

    std::string encodedMessage = encodeFIXMessage(sampleMessage);
    std::cout << "Message encodé : " << encodedMessage << std::endl;

    std::map<int, std::string> decodedMessage = decodeFIXMessage(encodedMessage);
    std::cout << "Message décodé : ";
    for (const auto& field : decodedMessage) {
        std::cout << field.first << "=" << field.second << " ";
    }
    std::cout << std::endl;

    return 0;
}
