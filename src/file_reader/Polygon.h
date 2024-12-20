#ifndef _POLYGON_H_
#define _POLYGON_H_

#include "RawElement.h"

class PolyGon : public RawElement {
private:
    std::vector<Gdiplus::PointF> points;
public:
    std::vector<Gdiplus::PointF> getPoints() const;
    ElementType getType() const;
    void print() const override;
    PolyGon(std::string points, const Stroke& stroke, const Fill& fill, const Transform& transform);
};

#endif