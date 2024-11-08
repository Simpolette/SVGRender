#include "Rect.h"

Rectan::Rectan(Gdiplus::Point coord, int width, int height, const Stroke& stroke, const Fill& fill) 
: RawElement(stroke, fill) {
    this->coord = coord;
    this->width = width;
    this->height = height;
}

Gdiplus::Point Rectan::getPoint() const{
    return coord;
}

int Rectan::getWidth() const{
    return width;
}

int Rectan::getHeight() const{
    return height;
}

ElementType Rectan::getType() const {
    return ElementType::RECTANGLE;
}