#include "Gradient.h"

Gradient::Gradient() {
    this->units = "objectBoundingBox";
    this->transform = "None";
    this->spreadMethod = "pad";

}

Gradient::Gradient(std::string id, std::string units, std::string transform, std::string spreadMethod, std::vector<Stop> stops) {
    this->id = id;
    this->units = units;
    this->transform = transform;
    this->spreadMethod = spreadMethod;
    this->stops = stops;
} 

std::string Gradient::getUnits() const {
    return this->units;
}

std::string Gradient::getTransform() const {
    return this->transform;
}

std::string Gradient::getSpreadMethod() const {
    return this->spreadMethod;
}

std::vector<Stop> Gradient::getStops() const {
    return this->stops;
}

std::string Gradient::getID() const {
    return this->id;
}