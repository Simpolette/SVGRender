#ifndef _ELLIPSE_H_
#define _ELLIPSE_H_

#include "RawElement.h"

class Ellip : public RawElement {
private:
    Gdiplus::Point coord;
    int rx, ry;
public:
    Gdiplus::Point getPoint() const;
    int getRX() const;
    int getRY() const;
    ElementType getType() const;
    void print() const override;
    Ellip(Gdiplus::Point coord, int rx, int ry, const Stroke& stroke, const Fill& fill, const Transform& transform); 
};


#endif