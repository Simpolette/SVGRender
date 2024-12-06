#ifndef _RAW_ELEMENT_H_
#define _RAW_ELEMENT_H_

#include <string>
#include <Windows.h>
#include <Gdiplus.h>
#include <vector>
#include <iostream>
#include <sstream>

#include "Stroke.h"
#include "Fill.h"
#include "Transform.h"

enum class ElementType{
    LINE,
    POLYLINE,
    POLYGON,
    CIRCLE,
    ELLIPSE,
    TEXT,
    RECTANGLE,
    GROUP,
    PATH,
};

class RawElement{
    
protected:
    Stroke stroke;
    Fill fill;
    Transform transform;
public:
    virtual ElementType getType() const = 0;
    Fill getFill() const;
    Stroke getStroke() const;
    Transform getTransform() const;
    void setTransform(Transform trans);
    virtual void print() const;
    RawElement();
    RawElement(const Stroke& stroke, const Fill& fill, const Transform& transform);
};

#endif