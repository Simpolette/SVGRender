#include "Group.h"

Group::Group(std::vector<RawElement*> re, const Stroke& stroke, const Fill& fill, const Transform& transform) 
: RawElement(stroke, fill, transform) {
    this->re = re;
}

ElementType Group::getType() const {
    return ElementType::GROUP;
}

std::vector<RawElement*> Group::getRawElement() const {
    return re;
}

void Group::print() const{
    std::cout << "Type: Group\n";
    RawElement::print();
    for (int i = 0; i < re.size(); i++){
        re[i]->print();
        std::cout << "\n";
    }
}