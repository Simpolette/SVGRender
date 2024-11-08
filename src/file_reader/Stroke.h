#ifndef _STROKE_H_
#define _STROKE_H_

#include <string>
#include <sstream>
#include <vector>
#include <windows.h>
#include <Gdiplus.h>
#include "function.h"

class Stroke{
private:
    Gdiplus::Color stroke;
    int stroke_width;
    double stroke_opacity;
    std::string stroke_linecap;
    std::vector<double> stroke_dasharray;
    std::string stroke_linejoin;
public:
    Stroke();
    Stroke(std::string color, int stroke_width, double stroke_opacity, std::string stroke_linecap, std::vector<double> stroke_dasharray, std::string stroke_linejoin);
    Gdiplus::Color getColorA() const;
    double getOpacity() const;
    int getWidth() const;
};

#endif