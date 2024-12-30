#ifndef _LINEAR_GRADIENT_H_
#define _LINEAR_GRADIENT_H_

#include <string>

#include "Gradient.h"

class LinearGradient : public Gradient{
private:
    Gdiplus::PointF p1, p2;
public:
    LinearGradient(std::string units, Transform transform, std::string spreadMethod, std::vector<Stop> stops, Gdiplus::PointF p1, Gdiplus::PointF p2);
    Gdiplus::Brush* getBrush(const Gdiplus::RectF& bound) const override;
    void print() const override;
};

#endif