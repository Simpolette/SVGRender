#include "RadialGradient.h"

RadialGradient::RadialGradient(std::string units, Transform transform, std::string spreadMethod, std::vector<Stop> stops, Gdiplus::PointF centerPoint, double radius, Gdiplus::PointF fCenterPoint, double fRadius)
: Gradient(units, transform, spreadMethod, stops) {
    this->centerPoint = centerPoint;
    this->radius = radius;
    this->fCenterPoint = fCenterPoint;
    this->fRadius = fRadius;
}

Gdiplus::Brush* RadialGradient::getBrush(const Gdiplus::RectF& bound) const {
    Gdiplus::RectF gradientBound(bound);
    if (units == "userSpaceOnUse"){
        gradientBound.X = centerPoint.X - radius;
        gradientBound.Y = centerPoint.Y - radius;
        gradientBound.Width = radius * 2;
        gradientBound.Height = radius * 2;
    }

    Gdiplus::GraphicsPath gradientPath;
    gradientPath.AddEllipse(gradientBound);

    Gdiplus::PathGradientBrush* brush = new Gdiplus::PathGradientBrush(&gradientPath);
    int stopCount = stops.size();
    Gdiplus::Color* colors = new Gdiplus::Color[stopCount + 2];
    Gdiplus::REAL* offsets = new Gdiplus::REAL[stopCount + 2];    
    
    colors[0] = stops[0].getColor();
    offsets[0] = 0;

    colors[stopCount + 1] = stops[stopCount - 1].getColor();
    offsets[stopCount + 1] = 1;

    for (int i = 0; i < stopCount; ++i) {
        colors[i + 1] = stops[i].getColor();
        offsets[i + 1] = stops[i].getOffset();
    }
    stopCount += 2;
    
    brush->SetInterpolationColors(colors, offsets, stopCount);
    brush->SetWrapMode(Gdiplus::WrapModeTileFlipXY);
    brush->MultiplyTransform(transform.getMatrix());

    delete[] colors;
    delete[] offsets;

    return brush;
}

void RadialGradient::print() const {
    Gradient::print();
    std::cout << "Type: RadialGradient\n";
    std::cout << "Center: " << centerPoint.X << " " << centerPoint.Y << "\n";
    std::cout << "Radius: " << radius << "\n";
    std::cout << "CenterF: " << fCenterPoint.X << " " << fCenterPoint.Y << "\n";
    std::cout << "RadiusF: " << fRadius << "\n";
}