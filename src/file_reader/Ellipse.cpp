#include "Ellipse.h"

Ellip::Ellip(Gdiplus::PointF coord, int rx, int ry, const Stroke& stroke, const Fill& fill, const Transform& transform) 
: RawElement(stroke, fill, transform) {
    this->coord = coord;
    this->rx = rx;
    this->ry = ry;
}

Gdiplus::PointF Ellip::getPoint() const {
    return coord;
}

int Ellip::getRX() const {
    return rx;
}

int Ellip::getRY() const {
    return ry;
}

ElementType Ellip::getType() const {
    return ElementType::ELLIPSE;
}

void Ellip::print() const{
    std::cout << "Type: Ellipse\n";
    RawElement::print();
    std::cout << "Center: (" << coord.X << ", " << coord.Y << ")\n";
    std::cout << "Radius: X:" << rx << " Y: " << ry << "\n";
}