#include "RawElement.h"

RawElement::RawElement(const Stroke& stroke, const Fill& fill, const Transform& transform){
    this->stroke = stroke;
    this->fill = fill;
    this->transform = transform;
}

Fill RawElement::getFill() const {
    return this->fill;
}

Stroke RawElement::getStroke() const {
    return this->stroke;
}

Transform RawElement::getTransform() const {
    return this->transform;
}

void RawElement::print() const{
    stroke.print();
    fill.print();
    transform.print();
}