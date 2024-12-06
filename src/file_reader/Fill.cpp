#include "Fill.h"

Fill::Fill(){
    this->color = Gdiplus::Color(0, 0, 0);
    this->opacity = 1;
    this->rule = "nonezero";
}

Fill::Fill(std::string color, double opacity, std::string rule){
    SVGColor fillColor(color);
    this->color = Gdiplus::Color(fillColor.getR(), fillColor.getG(), fillColor.getB());
    this->opacity = opacity;
    this->rule = rule;
}

Gdiplus::Color Fill::getColorA() const {
    return color;
}

double Fill::getOpacity() const {
    return opacity;
}

void Fill::print() const{
    std::cout << "Fill:\n"; 
    std::cout << "Color: (" << (int)color.GetR() << ", " 
                            << (int)color.GetG() << ", " 
                            << (int)color.GetB() << ")\n";
    std::cout << "Opacity: " << opacity << "\n";
}