#include "function.h"

void getColor(const std::string& color, int& red, int& green, int& blue){
    if (color == ""){
        red = green = blue = 0;
        return;
    }
    std::istringstream iss(color);
    std::string temp;
    getline(iss, temp, '(');
    getline(iss, temp, ',');
    red = stoi(temp);
    getline(iss, temp, ',');
    green = stoi(temp);
    getline(iss, temp, ')');
    blue = stoi(temp);
}