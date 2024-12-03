#ifndef _GROUP_H_
#define _GROUP_H_

#include "RawElement.h"

#include <vector>

class Group : public RawElement{
private:
    std::vector<RawElement*> re;
public:
    ElementType getType() const;
    std::vector<RawElement*> getRawElement() const;
    void print() const override;
    Group(std::vector<RawElement*> re,const Stroke& stroke, const Fill& fill, const Transform& transform);
};

#endif
