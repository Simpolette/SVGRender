#include "RadialGradient.h"

RadialGradient::RadialGradient() : Gradient() {
    this->centerPoint = Gdiplus::PointF(0, 0);
    this->radius = 0;
    this->fCenterPoint = Gdiplus::PointF(0, 0);
    this->fRadius = 0;
}

RadialGradient::RadialGradient(std::string id, std::string units, std::string transform, std::string spreadMethod, std::vector<Stop> stops, Gdiplus::PointF centerPoint, double radius, Gdiplus::PointF fCenterPoint, double fRadius)
: Gradient(id, units, transform, spreadMethod, stops) {
    this->centerPoint = centerPoint;
    this->radius = radius;
    this->fCenterPoint = fCenterPoint;
    this->fRadius = fRadius;
}

Gdiplus::PointF RadialGradient::getCenterPoint() {
    return this->centerPoint;
}

double RadialGradient::getRadius() {
    return this->radius;
}

Gdiplus::PointF RadialGradient::getFCenterPoint() {
    return this->fCenterPoint;
}
    
double RadialGradient::getFRadius() {
    return this->fRadius;
}