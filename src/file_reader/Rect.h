#ifndef _RECT_H_
#define _RECT_H_

#include "RawElement.h"

class Rectan : public RawElement {
private:
    Gdiplus::Point coord;
    int width, height;
public:
    Gdiplus::Point getPoint() const;
    int getWidth() const;
    int getHeight() const;
    ElementType getType() const;
    Rectan(Gdiplus::Point coord, int width, int height, const Stroke& stroke, const Fill& fill);
};

#endif