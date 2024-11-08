#include "Line.h"

Line::Line(Gdiplus::Point p1, Gdiplus::Point p2, const Stroke& stroke, const Fill& fill)
: RawElement(stroke, fill) {
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
