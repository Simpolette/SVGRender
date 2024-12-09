#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include "RawElement.h"

class Circle : public RawElement {
private:
    Gdiplus::PointF coord;
    int radius;
public:
    Gdiplus::PointF getPoint() const;
    int getRadius() const;
    ElementType getType() const;
    void print() const override;
    Circle(Gdiplus::PointF coord, int radius, const Stroke& stroke, const Fill& fill, const Transform& transform);
};

#endif