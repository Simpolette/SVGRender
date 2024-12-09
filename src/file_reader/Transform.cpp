#include "Transform.h"

Transform::Transform(Gdiplus::PointF translate, Gdiplus::PointF scale, double rotate) {
    this->translate = translate;
    this->scale = scale;
    this->rotate = rotate;
}

Transform::Transform() {
    this->rotate = 0;
    this->translate = Gdiplus::PointF(0, 0);
    this->scale = Gdiplus::PointF(0, 0);
}

Gdiplus::PointF Transform::getTranslate() const {
    return this->translate;
}

Gdiplus::PointF Transform::getScale() const {
    return this->scale;
}

double Transform::getRotate() const {
    return this->rotate;
}

void Transform::print() const{
    std::cout << "Transform:\n"; 
    std::cout << "Translate: (" << translate.X << ", " << translate.Y << ")\n";
    std::cout << "Scale: (" << scale.X << ", " << scale.Y << ")\n";
    std::cout << "Rotate: " << rotate << "\n";
}