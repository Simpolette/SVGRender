#include "LinearGradient.h"

LinearGradient::LinearGradient() : Gradient() { 
    p1 = Gdiplus::PointF(0, 0);
    p2 = Gdiplus::PointF(0, 0);
}

LinearGradient::LinearGradient(std::string id, std::string units, std::string transform, std::string spreadMethod, std::vector<Stop> stops, Gdiplus::PointF p1, Gdiplus::PointF p2) 
: Gradient(id, units, transform, spreadMethod, stops) {
    this->p1 = p1;
    this->p2 = p2;
}

Gdiplus::PointF LinearGradient::getPoint1() {
    return this->p1;
}

Gdiplus::PointF LinearGradient::getPoint2() {
    return this->p2;
}