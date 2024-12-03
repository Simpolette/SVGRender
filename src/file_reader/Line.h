#ifndef _LINE_H_
#define _LINE_H_

#include "RawElement.h"

class Line : public RawElement {

private:
    Gdiplus::Point p1, p2;
public:
    Gdiplus::Point getPointStart() const;
    Gdiplus::Point getPointEnd() const;
    ElementType getType() const;
    void print() const override;
    Line(Gdiplus::Point p1, Gdiplus::Point p2, const Stroke& stroke, const Fill& fill, const Transform& transform);
};

#endif