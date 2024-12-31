#ifndef _STOP_H_
#define _STOP_H_

#include <windows.h>
#include <Gdiplus.h>

#include "SVGColor.h"

class Stop {
private:
    double offset;
    Gdiplus::Color color;
    double opacity;
public:
    Stop(double offset, std::string color, double opacity);
    double getOffset() const;
    Gdiplus::Color getColor() const;
    double getOpacity() const;
    void print() const;
    void convertFromStyle(const std::string &style);
    double getDoubleValue(const std::string &s);
};

#endif