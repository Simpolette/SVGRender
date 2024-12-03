#ifndef _POLYGON_H_
#define _POLYGON_H_

#include "RawElement.h"

class PolyGon : public RawElement {
private:
    std::vector<Gdiplus::Point> points;
public:
    std::vector<Gdiplus::Point> getPoints() const;
    ElementType getType() const;
    void print() const override;
    PolyGon(std::string points, const Stroke& stroke, const Fill& fill, const Transform& transform);
};

#endif