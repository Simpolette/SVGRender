#include "Transform.h"

Transform::Transform(Gdiplus::Point translate, Gdiplus::Point scale, double rotate) {
    this->translate = translate;
    this->scale = scale;
    this->rotate = rotate;
}

Transform::Transform() {
    this->rotate = 0;
    this->translate = Gdiplus::Point(0, 0);
    this->scale = Gdiplus::Point(0, 0);
}

Gdiplus::Point Transform::getTranslate() const {
    return this->translate;
}

Gdiplus::Point Transform::getScale() const {
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