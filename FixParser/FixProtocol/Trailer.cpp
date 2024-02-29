#include "Trailer.h"

std::string Trailler::traillerCalculated(std::string body) {
    std::string trailler = "";
    int sum = 0;
    for (char c : body) {
        sum += c; // Ajoute la valeur ASCII de chaque caractère
    }
    int temp = sum % 256;
    trailler = std::to_string(temp); // Retourne le résultat modulo 256
    return trailler;
}

std::string Trailler::TraillerMaker(std::string body) {
    std::string trailler = "";
    trailler.append("10=" );
    trailler.append(traillerCalculated(body));
    return trailler;
}