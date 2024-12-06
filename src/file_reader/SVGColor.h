#ifndef _SVG_COLOR_H_
#define _SVG_COLOR_H_

#include <iostream>
#include <string>
#include <sstream>

class SVGColor{

private:
    int r;
    int g;
    int b;

public:
    SVGColor(const std::string& color);
    int getR() const;
    int getG() const;
    int getB() const;
};


#endif