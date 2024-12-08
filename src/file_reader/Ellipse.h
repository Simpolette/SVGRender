#ifndef _ELLIPSE_H_
#define _ELLIPSE_H_

#include "RawElement.h"

class Ellip : public RawElement {
private:
    Gdiplus::PointF coord;
    int rx, ry;
public:
    Gdiplus::PointF getPoint() const;
    int getRX() const;
    int getRY() const;
    ElementType getType() const;
    void print() const override;
    Ellip(Gdiplus::PointF coord, int rx, int ry, const Stroke& stroke, const Fill& fill, const Transform& transform); 
};


#endif