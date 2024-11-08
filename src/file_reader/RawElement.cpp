#include "RawElement.h"

RawElement::RawElement(){
    this->stroke = Stroke();
    this->fill = Fill();
}

RawElement::RawElement(const Stroke& stroke, const Fill& fill){
    this->stroke = stroke;
    this->fill = fill;
}

Fill RawElement::getFill() const {
    return fill;
}

Stroke RawElement::getStroke() const {
    return stroke;
}