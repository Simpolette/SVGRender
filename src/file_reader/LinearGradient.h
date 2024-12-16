#ifndef _LINEAR_GRADIENT_H_
#define _LINEAR_GRADIENT_H_

#include <string>

#include "Gradient.h"

class LinearGradient : public Gradient{
private:
    Gdiplus::PointF p1, p2;
public:
    LinearGradient();
    LinearGradient(std::string id, std::string units, std::string transform, std::string spreadMethod, std::vector<Stop> stops, Gdiplus::PointF p1, Gdiplus::PointF p2);
    Gdiplus::PointF getPoint1();
    Gdiplus::PointF getPoint2();
};

#endif