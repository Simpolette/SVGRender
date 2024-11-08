#include "Circle.h"

Circle::Circle(Gdiplus::Point coord, int radius, const Stroke& stroke, const Fill& fill)
: RawElement(stroke, fill) {
    this->coord = coord;
    this->radius = radius;
}

Gdiplus::Point Circle::getPoint() const{
    return coord;
}

int Circle::getRadius() const{
    return radius;
}

ElementType Circle::getType() const {
    return ElementType::CIRCLE;
}
