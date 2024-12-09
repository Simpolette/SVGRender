#include "Stroke.h"

Stroke::Stroke(){
    this->color = Gdiplus::Color(0, 0, 0);
    this->width = 1;
    this->opacity = 1;
    this->linecap = "butt";
    this->dasharray.clear();
    this->linejoin = "miter";
    this->miterlimit = 4;
}

Stroke::Stroke(std::string color, double width, double opacity, std::string linecap, std::vector<double> dasharray, std::string linejoin, double miterlimit){
    SVGColor fillColor(color);
    this->color = Gdiplus::Color(fillColor.getR(), fillColor.getG(), fillColor.getB());
    this->width = width;
    this->opacity = opacity;
    this->linecap = linecap;
    this->dasharray.clear();
    this->linejoin = linejoin;
    this->miterlimit = miterlimit;

    if (color != ""){
        this->opacity = 1;
    }
    
}

Gdiplus::Color Stroke::getColorA() const {
    return color;
}

double Stroke::getOpacity() const {
    return opacity;
}

double Stroke::getWidth() const{
    return width;
}

double Stroke::getMiterLimit() const{
    return miterlimit;
}

void Stroke::print() const{
    std::cout << "Stroke:\n"; 
    std::cout << "Color: (" << (int)color.GetR() << ", " 
                            << (int)color.GetG() << ", " 
                            << (int)color.GetB() << ")\n";
    std::cout << "Opacity: " << opacity << "\n";
    std::cout << "Width: " << width << "\n";
    std::cout << "Mitter limit: " << miterlimit << "\n";
}