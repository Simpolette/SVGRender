#include "SVGColor.h"

extern std::unordered_map<std::string, Gdiplus::Color> mpColorName;

int SVGColor::getValue(const std::string& s) const {
    return std::stoi(s, NULL, 16);
}

std::string SVGColor::getLower(const std::string &color) const {
    int n = color.size();
    std::string res;
    for (int i = 0; i < n; i++) {
        if (color[i] >= 'A' && color[i] <= 'Z') {
            res += char(color[i] + 32);
        }
        else {
            res += char(color[i]);
        }
    }
}

SVGColor::SVGColor(const std::string& color){
    if (color == ""){
        r = g = b = 0;
        return;
    }
    std::string temp = getLower(color);
    if (mpColorName.find(temp) != mpColorName.end()) {
        r = mpColorName[temp].GetRed();
        g = mpColorName[temp].GetGreen();
        b = mpColorName[temp].GetBlue();
        return;

    }

    if (color.find("rgb")) {
        std::istringstream iss(color);
        std::string temp;
        getline(iss, temp, '(');
        getline(iss, temp, ',');
        r = stoi(temp);
        getline(iss, temp, ',');
        g = stoi(temp);
        getline(iss, temp, ')');
        b = stoi(temp);
        return;
    }

    if (color == "#FFF") {
        r = 255;
        g = 255;
        b = 255;
        return;
    }
    if (color == "#000") {
        r = 0;
        g = 0;
        b = 0;
        return;
    }

    std::string redTemp = color.substr(0, 2);
    std::string greenTemp = color.substr(2, 2);
    std::string blueTemp = color.substr(4, 2);

    r = getValue(redTemp);
    g = getValue(greenTemp);
    b = getValue(blueTemp);
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
