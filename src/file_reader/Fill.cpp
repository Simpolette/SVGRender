#include "Fill.h"

Fill::Fill(){
    this->color = Gdiplus::Color(0, 0, 0);
    this->opacity = 1;
    this->rule = "nonezero";
    this->gradient = NULL;
}

Fill::Fill(std::string color, double opacity, std::string rule, Gradient* gradient) {
    if (!gradient){
        SVGColor fillColor(color);
        this->color = Gdiplus::Color(fillColor.getR(), fillColor.getG(), fillColor.getB());
    }
    else{
        this->color = Gdiplus::Color(0, 0, 0);
    }
    this->opacity = opacity;
    this->rule = rule;
    this->gradient = gradient;
}

std::string Fill::getRule() const {
    return rule;
}

Gdiplus::Brush* Fill::getBrush() const {
    Gdiplus::Brush* brush = NULL;

    if (!gradient){
        Gdiplus::Color brushColor(
            static_cast<BYTE>(opacity * 255), 
            color.GetRed(),
            color.GetGreen(),
            color.GetBlue()
        );
        brush = new Gdiplus::SolidBrush(brushColor);    
    }

    return brush;
}

Gdiplus::Brush* Fill::getGradientBrush(const Gdiplus::RectF& bound) const {
    if (!gradient){
        return NULL;
    }

    return gradient->getBrush(bound);
}

void Fill::print() const{
    std::cout << "Fill:\n"; 
    if (!gradient){
        std::cout << "Color: (" << (int)color.GetR() << ", " 
                                << (int)color.GetG() << ", " 
                                << (int)color.GetB() << ")\n";
        std::cout << "Opacity: " << opacity << "\n";
    }
    else{
        gradient->print();
    }
}