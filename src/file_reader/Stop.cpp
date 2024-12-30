#include "Stop.h"

Stop::Stop(double offset, std::string color, double opacity) {
    SVGColor stopColor(color);
    this->offset = offset;
    this->color = Gdiplus::Color(stopColor.getR(), stopColor.getG(), stopColor.getB());
    this->opacity = opacity;
}

double Stop::getOffset() const {
    return this->offset;
}

Gdiplus::Color Stop::getColor() const {
    return this->color;
}

double Stop::getOpacity() const {
    return this->opacity;
}

void Stop::print() const {
    std::cout << "Offset: " << offset << "\n";
    std::cout << "Color: (" << (int)color.GetR() << ", " 
                            << (int)color.GetG() << ", " 
                            << (int)color.GetB() << ")\n";
    std::cout << "Opacity: " << opacity << "\n";
}