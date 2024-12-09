#include "Rect.h"

Rectan::Rectan(Gdiplus::PointF coord, int width, int height, const Stroke& stroke, const Fill& fill, const Transform& transform) 
: RawElement(stroke, fill, transform) {
    this->coord = coord;
    this->width = width;
    this->height = height;
}

Gdiplus::PointF Rectan::getPoint() const{
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

void Rectan::print() const{
    std::cout << "Type: Rectangle\n";
    RawElement::print();
    std::cout << "Top-left corner: (" << coord.X << ", " << coord.Y << ")\n";
    std::cout << "Width: " << width << "\n";
    std::cout << "Height: " << height << "\n";
}