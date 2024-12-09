#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include <windows.h>
#include <Gdiplus.h>
#include <iostream>

class Transform{
private:
    Gdiplus::PointF translate;
    Gdiplus::PointF scale;
    double rotate;
public:
    Gdiplus::PointF getTranslate() const;
    Gdiplus::PointF getScale() const;
    double getRotate() const;
    Transform();
    Transform(Gdiplus::PointF translate, Gdiplus::PointF scale, double rotate);
    void print() const;
};

#endif