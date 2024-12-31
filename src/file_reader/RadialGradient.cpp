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
    Gdiplus::PointF newFCenter(fCenterPoint);
    if (units == "userSpaceOnUse"){
        gradientBound.X = centerPoint.X - radius;
        gradientBound.Y = centerPoint.Y - radius;
        gradientBound.Width = radius * 2;
        gradientBound.Height = radius * 2;
    }
    else if (units == "objectBoundingBox"){
        newFCenter.X = bound.X + bound.Width * centerPoint.X;
        newFCenter.Y = bound.Y + bound.Height * centerPoint.Y;   
    }
    // Gdiplus::Matrix* transformMatrix = transform.getMatrix();
    // Gdiplus::PointF points[5] = {
    //     Gdiplus::PointF(gradientBound.X, gradientBound.Y),                          // Top-left
    //     Gdiplus::PointF(gradientBound.X + gradientBound.Width, gradientBound.Y),    // Top-right
    //     Gdiplus::PointF(gradientBound.X, gradientBound.Y + gradientBound.Height),   // Bottom-left
    //     Gdiplus::PointF(gradientBound.X + gradientBound.Width, gradientBound.Y + gradientBound.Height), // Bottom-right
    //     Gdiplus::PointF(fCenterPoint)
    // };

    // // Calculating new bound points
    // transformMatrix->TransformPoints(points, 5);

    // Gdiplus::REAL minX = points[0].X;
    // Gdiplus::REAL minY = points[0].Y;
    // // Getting new gradient bound
    // for (int i = 1; i < 4; i++){
    //     minX = std::min(minX, points[i].X);
    //     minY = std::min(minY, points[i].Y);
    // }


    Gdiplus::GraphicsPath gradientPath;
    gradientPath.AddEllipse(gradientBound);
    // gradientPath.AddRectangle(gradientBound);

    Gdiplus::PathGradientBrush* brush = new Gdiplus::PathGradientBrush(&gradientPath);
    brush->SetCenterPoint(newFCenter); 
    brush->SetCenterColor(stops[0].getColor());
    int stopCount = stops.size();
    Gdiplus::Color* colors = new Gdiplus::Color[stopCount + 2];
    Gdiplus::REAL* offsets = new Gdiplus::REAL[stopCount + 2];    
    
    colors[0] = stops[0].getColor();
    offsets[0] = 0;

    colors[stopCount + 1] = stops[stopCount - 1].getColor();
    offsets[stopCount + 1] = 1;

    for (int i = 0; i < stopCount; ++i) {
        colors[i + 1] = stops[stopCount - i - 1].getColor();
        offsets[i + 1] = 1 - stops[stopCount - i - 1].getOffset();
    }
    stopCount += 2;
    
    brush->SetInterpolationColors(colors, offsets, stopCount);
    // brush->SetWrapMode(Gdiplus::WrapModeClamp);
    brush->SetTransform(transform.getMatrix());

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