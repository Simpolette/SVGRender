#include "SVGColor.h"

extern std::unordered_map<std::string, Gdiplus::Color> mpColorName;

int SVGColor::getValue(const std::string& s) const {
    return std::stoi(s, NULL, 16);
}

SVGColor::SVGColor() {
    r = g = b = 0;
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
        std::string redTemp;
        std::string greenTemp;
        std::string blueTemp;
        if (color.size() == 7){
            redTemp = color.substr(1, 2);
            greenTemp = color.substr(3, 2);
            blueTemp = color.substr(5, 2);
        }
        else if (color.size() == 4){
            redTemp = color.substr(1, 1);
            redTemp += redTemp;
            greenTemp = color.substr(2, 1);
            greenTemp += greenTemp;
            blueTemp = color.substr(3, 1);
            blueTemp += blueTemp;
        }
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
