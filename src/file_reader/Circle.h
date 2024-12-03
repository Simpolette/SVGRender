#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include "RawElement.h"

class Circle : public RawElement {
private:
    Gdiplus::Point coord;
    int radius;
public:
    Gdiplus::Point getPoint() const;
    int getRadius() const;
    ElementType getType() const;
    void print() const override;
    Circle(Gdiplus::Point coord, int radius, const Stroke& stroke, const Fill& fill, const Transform& transform);
};

#endif