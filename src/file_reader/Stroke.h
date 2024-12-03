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
    Gdiplus::Color color;
    int width;
    double opacity;
    std::string linecap;
    std::vector<double> dasharray;
    std::string linejoin;
public:
    Stroke();
    Stroke(std::string color, int width, double opacity, std::string linecap, std::vector<double> dasharray, std::string linejoin);
    Gdiplus::Color getColorA() const;
    double getOpacity() const;
    int getWidth() const;
    void print() const;
};

#endif