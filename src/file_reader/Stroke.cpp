#include "Stroke.h"

Stroke::Stroke(){
    this->stroke = Gdiplus::Color(0, 0, 0);
    this->stroke_width = 1;
    this->stroke_opacity = 1;
    this->stroke_linecap = "butt";
    this->stroke_dasharray.clear();
    this->stroke_linejoin = "miter";
}

Stroke::Stroke(std::string color, int stroke_width, double stroke_opacity, std::string stroke_linecap, std::vector<double> stroke_dasharray, std::string stroke_linejoin){
    int red, green, blue;

    getColor(color, red, green, blue);
    this->stroke = Gdiplus::Color(red, green, blue);
    this->stroke_width = stroke_width;
    this->stroke_opacity = stroke_opacity;
    this->stroke_linecap = stroke_linecap;
    this->stroke_dasharray.clear();
    this->stroke_linejoin = stroke_linejoin;
}

Gdiplus::Color Stroke::getColorA() const {
    return stroke;
}

double Stroke::getOpacity() const {
    return stroke_opacity;
}

int Stroke::getWidth() const{
    return stroke_width;
}
