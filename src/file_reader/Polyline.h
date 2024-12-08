#ifndef _POLYLINE_H_
#define _POLYLINE_H_

#include "RawElement.h"

class PolyLine : public RawElement {
private:
    std::vector<Gdiplus::PointF> points;
public:
    std::vector<Gdiplus::PointF> getPoints() const;
    ElementType getType() const;
    void print() const override;
    PolyLine(std::string points, const Stroke& stroke, const Fill& fill, const Transform& transform);
};

#endif