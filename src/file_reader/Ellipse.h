#ifndef _ELLIPSE_H_
#define _ELLIPSE_H_

#include "RawElement.h"

class Ellip : public RawElement {
private:
    Gdiplus::PointF coord;
    double rx, ry;
public:
    Gdiplus::PointF getPoint() const;
    double getRX() const;
    double getRY() const;
    ElementType getType() const;
    void print() const override;
    Ellip(Gdiplus::PointF coord, double rx, double ry, const Stroke& stroke, const Fill& fill, const Transform& transform); 
};


#endif