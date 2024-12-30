#ifndef _STROKE_H_
#define _STROKE_H_

#include <string>
#include <sstream>
#include <vector>
#include <windows.h>
#include <Gdiplus.h>
#include "SVGColor.h"

class Stroke{
private:
    Gdiplus::Color color;
    double width;
    double opacity;
    std::string linecap;
    std::vector<double> dasharray;
    std::string linejoin;
    double miterlimit;
public:
    Stroke();
    Stroke(std::string color, double width, double opacity, std::string linecap, std::vector<double> dasharray, std::string linejoin, double stroke_miterlimit);
    Gdiplus::Pen* getPen() const;
    void print() const;
};

#endif