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
    RadialGradient();
    RadialGradient(std::string id, std::string units, std::string transform, std::string spreadMethod, std::vector<Stop> stops, Gdiplus::PointF centerPoint, double radius, Gdiplus::PointF fCenterPoint, double fRadius);
    Gdiplus::PointF getCenterPoint();
    double getRadius();
    Gdiplus::PointF getFCenterPoint();
    double getFRadius();
};

#endif