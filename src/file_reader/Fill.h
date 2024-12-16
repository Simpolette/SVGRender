#ifndef _FILL_H_
#define _FILL_H_

#include <string>
#include <sstream>
#include <windows.h>
#include <Gdiplus.h>

#include "SVGColor.h"
#include "Gradient.h"
#include "LinearGradient.h"
#include "RadialGradient.h"

class Fill{
private:
    Gdiplus::Color color;
    double opacity;
    std::string rule;
    Gradient* gradient;
public:
    Fill();
    Fill(std::string color, double opacity, std::string rule, Gradient* gradient);
    Gdiplus::Color getColorA() const;
    double getOpacity() const;
    std::string getRule() const;
    void print() const;
};

#endif