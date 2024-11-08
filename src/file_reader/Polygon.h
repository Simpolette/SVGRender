#ifndef _POLYGON_H_
#define _POLYGON_H_

#include "RawElement.h"

class PolyGon : public RawElement {
private:
    std::vector<Gdiplus::Point> points;
public:
    std::vector<Gdiplus::Point> getPoints() const;
    ElementType getType() const;
    PolyGon(std::string points, const Stroke& stroke, const Fill& fill);
};

#endif