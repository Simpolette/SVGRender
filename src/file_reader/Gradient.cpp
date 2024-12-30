#include "Gradient.h"

Gradient::Gradient(std::string units, Transform transform, std::string spreadMethod, std::vector<Stop> stops) {
    this->units = units;
    this->transform = transform;
    this->spreadMethod = spreadMethod;
    this->stops = stops;
} 

void Gradient::print() const {
    std::cout << "Gradient: \n";
    std::cout << "Unit: " << units << "\n";
    transform.print();
    std::cout << "Spread method: " << spreadMethod << "\n";
    for (int i = 0; i < stops.size(); i++){
        std::cout << "Stop " << i + 1 << ":\n";
        stops[i].print();
    }
}