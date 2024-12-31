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
    std::string getRule() const;
    Gdiplus::Brush* getBrush() const;
    Gdiplus::Brush* getGradientBrush(const Gdiplus::RectF& bound) const;
    void convertFromStyle(const std::string &style, std::string& id);
    void print() const;
    void setGradient(Gradient* gradient);
};

#endif