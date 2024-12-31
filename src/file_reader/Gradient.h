#ifndef _GRADIENT_H_
#define _GRADIENT_H_

#include <string>
#include <vector>

#include "Stop.h"
#include "Transform.h"

class Gradient {
protected:
    std::string units;
    Transform transform;
    std::string spreadMethod;
    std::vector<Stop> stops;
public:
    Gradient(std::string units, Transform transform, std::string spreadMethod, std::vector<Stop> stops);
    virtual Gdiplus::Brush* getBrush(const Gdiplus::RectF& bound) const = 0;
    virtual void print() const;
    std::string getUnits() const;
    Transform getTransform() const;
    std::string getSpreadMethod() const;
    std::vector<Stop> getStops() const;
};

#endif