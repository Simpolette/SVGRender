#include "SVGColor.h"

extern std::unordered_map<std::string, Gdiplus::Color> mpColorName;

int SVGColor::getValue(const std::string& s) const {
    return std::stoi(s, NULL, 16);
}

SVGColor::SVGColor(const std::string& color){
    if (color == ""){
        r = g = b = 0;
        return;
    }

    if (color.find("rgb") != std::string::npos){
        std::istringstream iss(color);
        std::string temp;
        getline(iss, temp, '(');
        getline(iss, temp, ',');
        r = stoi(temp);
        if (r > 255){
            r = 255;
        }
        getline(iss, temp, ',');
        g = stoi(temp);
        if (g > 255){
            g = 255;
        }
        getline(iss, temp, ')');
        b = stoi(temp);
        if (b > 255){
            b = 255;
        }
        return;
    }
    else if (mpColorName.find(color) != mpColorName.end()){
        r = mpColorName[color].GetRed();
        g = mpColorName[color].GetGreen();
        b = mpColorName[color].GetBlue();
        return;
    }
    else if (color[0] == '#'){
        std::string redTemp = color.substr(1, 2);
        std::string greenTemp = color.substr(3, 2);
        std::string blueTemp = color.substr(5, 2);

        r = getValue(redTemp);
        g = getValue(greenTemp);
        b = getValue(blueTemp);
        
    }
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
