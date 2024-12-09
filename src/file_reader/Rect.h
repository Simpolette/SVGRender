#ifndef _RECT_H_
#define _RECT_H_

#include "RawElement.h"

class Rectan : public RawElement {
private:
    Gdiplus::PointF coord;
    double width, height;
public:
    Gdiplus::PointF getPoint() const;
    double getWidth() const;
    double getHeight() const;
    ElementType getType() const;
    void print() const override;
    Rectan(Gdiplus::PointF coord, double width, double height, const Stroke& stroke, const Fill& fill, const Transform& transform);
};

#endif