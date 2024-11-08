#include "Fill.h"

Fill::Fill(){
    this->color = Gdiplus::Color(1, 0, 0, 0);
    this->opacity = 1;
    this->rule = "nonezero";
}

Fill::Fill(std::string color, double opacity, std::string rule){
    int red, green, blue;

    getColor(color, red, green, blue);
    this->color = Gdiplus::Color(1, red, green, blue);
    this->opacity = opacity;
    this->rule = rule;
}

Gdiplus::Color Fill::getColorA() const {
    return color;
}

double Fill::getOpacity() const {
    return opacity;
}
