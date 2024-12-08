#ifndef _LINE_H_
#define _LINE_H_

#include "RawElement.h"

class Line : public RawElement {

private:
    Gdiplus::PointF p1, p2;
public:
    Gdiplus::PointF getPointStart() const;
    Gdiplus::PointF getPointEnd() const;
    ElementType getType() const;
    void print() const override;
    Line(Gdiplus::PointF p1, Gdiplus::PointF p2, const Stroke& stroke, const Fill& fill, const Transform& transform);
};

#endif