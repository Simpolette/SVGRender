#ifndef _GRADIENT_H_
#define _GRADIENT_H_

#include <string>
#include <vector>

#include "Stop.h"

class Gradient {
protected:
    std::string id;
    std::string units;
    std::string transform;
    std::string spreadMethod;
    std::vector<Stop> stops;
public:
    Gradient();
    Gradient(std::string id, std::string units, std::string transform, std::string spreadMethod, std::vector<Stop> stops);
    std::string getUnits() const;
    std::string getTransform() const;
    std::string getSpreadMethod() const;
    std::vector<Stop> getStops() const;

    std::string getID() const;

    /*virtual Gdiplus::PointF getPoint1() = 0;
    virtual Gdiplus::PointF getPoint2() = 0;

    virtual Gdiplus::PointF getCenterPoint() = 0;
    virtual double getRadius() = 0;
    virtual Gdiplus::PointF getFCenterPoint() = 0;
    virtual double getFRadius() = 0;*/
};

#endif