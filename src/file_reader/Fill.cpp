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

void Fill::convertFromStyle(const std::string &style, std::string& id){
    size_t pos = 0;
    std::string color;

    while (pos < style.length()) {
        size_t key_end = style.find(':', pos);
        size_t value_end = style.find(';', key_end);

        if (key_end == std::string::npos) {
            break;
        }
        if (value_end == std::string::npos) {
            value_end = style.length();
        }

        std::string key = style.substr(pos, key_end - pos);
        std::string value = style.substr(key_end + 1, value_end - key_end - 1);

        key.erase(0, key.find_first_not_of(" \t"));
        key.erase(key.find_last_not_of(" \t") + 1);
        value.erase(0, value.find_first_not_of(" \t"));
        value.erase(value.find_last_not_of(" \t") + 1);

        if (key == "fill"){
            color = value;
            if (color.find("url") != std::string::npos){
                // Handle color id
                if (color.find("'") != std::string::npos) {
                    id = color.substr(color.find("'") + 1);
                    id.erase(id.find("'"));
                    id.erase(id.find("#"), 1);
                } 
                else{
                    id = color.substr(color.find("#") + 1);
                    id.erase(id.find(")"));
                }
            }
            else{
                for (int i = 0; i < color.size(); i++){
                    color[i] = std::tolower(color[i]);
                }
                if (color.find("none") != std::string::npos){
                    opacity = 0;
                    color = "";
                    break;
                }
            }
        }
        else if (key == "fill-opacity"){
            opacity = stod(value);
        }
        else if (key == "opacity"){
            opacity = stod(value);
        }
        else if (key == "fill-rule"){
            rule = value;
        }

        if (value_end == std::string::npos) {
            pos = std::string::npos;
        }
        else {
            pos = value_end + 1;
        }
    }
    if (id == ""){
        SVGColor fillColor(color);
        this->color = Gdiplus::Color(fillColor.getR(), fillColor.getG(), fillColor.getB());
    }
}

void Fill::setGradient(Gradient* gradient){
    if (this->gradient != NULL){
        delete gradient;
    }
    this->gradient = gradient;
}