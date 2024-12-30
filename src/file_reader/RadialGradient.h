#ifndef _RADIAL_GRADIENT_H_
#define _RADIAL_GRADIENT_H_

#include <string>

#include "Gradient.h"

class RadialGradient : public Gradient {
private:
    Gdiplus::PointF centerPoint;
    double radius;
    Gdiplus::PointF fCenterPoint;
    double fRadius;
public:
    RadialGradient(std::string units, Transform transform, std::string spreadMethod, std::vector<Stop> stops, Gdiplus::PointF centerPoint, double radius, Gdiplus::PointF fCenterPoint, double fRadius);
    Gdiplus::Brush* getBrush(const Gdiplus::RectF& bound) const override;
    void print() const override;
};

#endif