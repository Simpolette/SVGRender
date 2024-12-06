#include "SVGColor.h"

SVGColor::SVGColor(const std::string& color){
    if (color == ""){
        r = g = b = 0;
        return;
    }
    std::istringstream iss(color);
    std::string temp;
    getline(iss, temp, '(');
    getline(iss, temp, ',');
    r = stoi(temp);
    getline(iss, temp, ',');
    g = stoi(temp);
    getline(iss, temp, ')');
    b = stoi(temp);
}

int SVGColor::getR() const{
    return r;
}

int SVGColor::getG() const{
    return g;
}

int SVGColor::getB() const{
    return b;
}
