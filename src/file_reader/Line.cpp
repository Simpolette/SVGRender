#include "Line.h"

Line::Line(Gdiplus::PointF p1, Gdiplus::PointF p2, const Stroke& stroke, const Fill& fill, const Transform& transform)
: RawElement(stroke, fill, transform) {
    this->p1 = p1;
    this->p2 = p2;
}

Gdiplus::PointF Line::getPointStart() const {
    return p1;
}

Gdiplus::PointF Line::getPointEnd() const {
    return p2;
}

ElementType Line::getType() const {
    return ElementType::LINE;
}

void Line::print() const{
    std::cout << "Type: Line\n";
    RawElement::print();
    std::cout << "Point 1: (" << p1.X << ", " << p1.Y << ")\n";
    std::cout << "Point 2: (" << p2.X << ", " << p2.Y << ")\n";
}