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
    std::string getID() const;
    virtual void print() const;
};

#endif