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

enum class ElementType{
    LINE,
    POLYLINE,
    POLYGON,
    CIRCLE,
    ELLIPSE,
    TEXT,
    RECTANGLE,
};

class RawElement{
    
protected:
    Stroke stroke;
    Fill fill;
    
public:
    virtual ElementType getType() const = 0;
    Fill getFill() const;
    Stroke getStroke() const;
    RawElement();
    RawElement(const Stroke& stroke, const Fill& fill);
};

#endif