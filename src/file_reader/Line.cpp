#include "Line.h"

Line::Line(Gdiplus::Point p1, Gdiplus::Point p2, const Stroke& stroke, const Fill& fill, const Transform& transform)
: RawElement(stroke, fill, transform) {
    this->p1 = p1;
    this->p2 = p2;
}

Gdiplus::Point Line::getPointStart() const {
    return p1;
}

Gdiplus::Point Line::getPointEnd() const {
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