#include <iostream>
#include <vector>
#include <string>

// Classe représentant un champ FIX
class FIXField {
private:
    int tag;
    std::string value;
public:
    FIXField(int tag, const std::string& value) : tag(tag), value(value) {}

    int getTag() const { return tag; }
    std::string getValue() const { return value; }
};

// Classe représentant un message FIX
class FIXMessage {
protected:
    std::vector<FIXField> fields;

    // Méthode pour ajouter un champ au message
    void addField(int tag, const std::string& value) {
        fields.push_back(FIXField(tag, value));
    }

    // Méthode pour sérialiser le message
    virtual std::string serialize() const {
        std::string result;
        for (const auto& field : fields) {
            result += std::to_string(field.getTag()) + "=" + field.getValue() + "|";
        }
        return result;
    }
public:
    // Méthode pour afficher le message
    void print() const {
        for (const auto& field : fields) {
            std::cout << "Tag: " << field.getTag() << ", Value: " << field.getValue() << std::endl;
        }
    }
};

// Classe représentant un message Logon (35=A)
class LogonMessage : public FIXMessage {
public:
    LogonMessage() {
        // Ajouter les champs requis pour le message Logon
        addField(35, "A");
        // Ajouter d'autres champs requis pour le Logon si nécessaire
    }
};

// Classe représentant un message NewOrder (35=D)
class NewOrderMessage : public FIXMessage {
public:
    NewOrderMessage() {
        // Ajouter les champs requis pour le message NewOrder
        addField(35, "D");
        // Ajouter d'autres champs requis pour le NewOrder si nécessaire
    }
};

// Ajouter d'autres classes pour les autres types de messages FIX (OrderCancelRequest, ExecutionReport, etc.)

int main() {
    // Exemple d'utilisation
    LogonMessage logon;
    logon.print();

    NewOrderMessage newOrder;
    newOrder.print();

    return 0;
}