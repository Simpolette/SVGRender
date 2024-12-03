#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include <windows.h>
#include <Gdiplus.h>
#include <iostream>

class Transform{
private:
    Gdiplus::Point translate;
    Gdiplus::Point scale;
    double rotate;
public:
    Gdiplus::Point getTranslate() const;
    Gdiplus::Point getScale() const;
    double getRotate() const;
    Transform();
    Transform(Gdiplus::Point translate, Gdiplus::Point scale, double rotate);
    void print() const;
};

#endif