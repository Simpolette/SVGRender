#ifndef _STOP_H_
#define _STOP_H_

#include <windows.h>
#include <Gdiplus.h>

#include "SVGColor.h"

class Stop {
private:
    double offset;
    SVGColor color;
    double opacity;
public:
    Stop();
    Stop(double offset, std::string color, double opacity);
    double getOffset() const;
    SVGColor getColor() const;
    double getOpacity() const;
};

#endif