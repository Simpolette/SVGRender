#include "Ellipse.h"

Ellip::Ellip(Gdiplus::Point coord, int rx, int ry, const Stroke& stroke, const Fill& fill) 
: RawElement(stroke, fill) {
    this->coord = coord;
    this->rx = rx;
    this->ry = ry;
}

Gdiplus::Point Ellip::getPoint() const {
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
