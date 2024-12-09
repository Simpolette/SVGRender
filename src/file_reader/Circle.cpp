#include "Circle.h"

Circle::Circle(Gdiplus::PointF coord, double radius, const Stroke& stroke, const Fill& fill, const Transform& transform)
: RawElement(stroke, fill, transform) {
    this->coord = coord;
    this->radius = radius;
}

Gdiplus::PointF Circle::getPoint() const{
    return coord;
}

double Circle::getRadius() const{
    return radius;
}

ElementType Circle::getType() const{
    return ElementType::CIRCLE;
}

void Circle::print() const{
    std::cout << "Type: Circle\n";
    RawElement::print();
    std::cout << "Center: (" << coord.X << ", " << coord.Y << ")\n";
    std::cout << "Radius: " << radius << "\n";
}
