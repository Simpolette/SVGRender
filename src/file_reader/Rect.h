#ifndef _RECT_H_
#define _RECT_H_

#include "RawElement.h"

class Rectan : public RawElement {
private:
    Gdiplus::PointF coord;
    int width, height;
public:
    Gdiplus::PointF getPoint() const;
    int getWidth() const;
    int getHeight() const;
    ElementType getType() const;
    void print() const override;
    Rectan(Gdiplus::PointF coord, int width, int height, const Stroke& stroke, const Fill& fill, const Transform& transform);
};

#endif