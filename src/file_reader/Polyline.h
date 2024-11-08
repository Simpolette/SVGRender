#ifndef _POLYLINE_H_
#define _POLYLINE_H_

#include "RawElement.h"

class PolyLine : public RawElement {
private:
    std::vector<Gdiplus::Point> points;
public:
    std::vector<Gdiplus::Point> getPoints() const;
    ElementType getType() const;
    PolyLine(std::string points, const Stroke& stroke, const Fill& fill);
};

#endif