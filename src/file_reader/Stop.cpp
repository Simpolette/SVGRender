#include "Stop.h"

Stop::Stop(double offset, std::string color, double opacity) {
    SVGColor stopColor(color);
    this->offset = offset;
    this->color = Gdiplus::Color(opacity * 255, stopColor.getR(), stopColor.getG(), stopColor.getB());
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

double Stop::getDoubleValue(const std::string &s) {
    if (s.find('%') != std::string::npos) {
        return stod(s.substr(0, s.find('%'))) / 100;
    }
    return stod(s);
}

void Stop::convertFromStyle(const std::string &style){
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
        if (key == "stop-color") {
            color = value;
            for (int i = 0; i < color.size(); i++){
                color[i] = std::tolower(color[i]);
            }
            if (color.find("none") != std::string::npos){
                opacity = 0;
                color = "";
                break;
            }
        }
        else if (key == "offset"){
            offset = getDoubleValue(value);
        }
        else if (key == "stop-opacity"){
            opacity = getDoubleValue(value);
        }

        if (value_end == std::string::npos) {
            pos = std::string::npos;
        }
        else {
            pos = value_end + 1;
        }
    }
    SVGColor fillColor(color);
    this->color = Gdiplus::Color(fillColor.getR(), fillColor.getG(), fillColor.getB());
}