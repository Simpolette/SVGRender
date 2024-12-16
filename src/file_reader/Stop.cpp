#include "Stop.h"

Stop::Stop() {
    this->offset = 0;
    this->color = SVGColor();
    this->opacity = 0;
}

Stop::Stop(double offset, std::string color, double opacity) {
    this->offset = offset;
    this->color = SVGColor(color);
    this->opacity = opacity;
}

double Stop::getOffset() const {
    return this->offset;
}

SVGColor Stop::getColor() const {
    return this->color;
}

double Stop::getOpacity() const {
    return this->opacity;
}