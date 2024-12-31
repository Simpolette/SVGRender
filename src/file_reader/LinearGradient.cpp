#include "LinearGradient.h"

LinearGradient::LinearGradient(std::string units, Transform transform, std::string spreadMethod, std::vector<Stop> stops, Gdiplus::PointF p1, Gdiplus::PointF p2) 
: Gradient(units, transform, spreadMethod, stops) {
    this->p1 = p1;
    this->p2 = p2;
}

Gdiplus::Brush* LinearGradient::getBrush(const Gdiplus::RectF& bound) const {
    int stopCount = stops.size();
    Gdiplus::Color* colors = new Gdiplus::Color[stopCount + 2];
    Gdiplus::REAL* offsets = new Gdiplus::REAL[stopCount + 2];    

    Gdiplus::PointF start = p1; 
    Gdiplus::PointF end = p2;

    Gdiplus::Matrix* matrix = transform.getMatrix();
    matrix->TransformPoints(&start); 
    matrix->TransformPoints(&end); 

    if (units == "objectBoundingBox"){        
        start = Gdiplus::PointF(bound.X + p1.X * bound.Width, bound.Y + p1.Y * bound.Height);
        end = Gdiplus::PointF(bound.X + p2.X * bound.Width, bound.Y + p2.Y * bound.Height);
    }

    colors[0] = stops[0].getColor();
    offsets[0] = 0;

    colors[stopCount + 1] = stops[stopCount - 1].getColor();
    offsets[stopCount + 1] = 1;

    for (int i = 0; i < stopCount; ++i) {
        colors[i + 1] = stops[i].getColor();
        offsets[i + 1] = (stops[i].getOffset());
    }
    stopCount += 2;
    
    Gdiplus::LinearGradientBrush* brush = new Gdiplus::LinearGradientBrush(
        start,
        end,
        stops[0].getColor(),
        stops[stopCount - 1].getColor()
    );

    brush->SetInterpolationColors(colors, offsets, stopCount);
    brush->SetWrapMode(Gdiplus::WrapModeClamp);

    delete[] colors;
    delete[] offsets;
    delete matrix;

    return brush;
}

void LinearGradient::print() const {
    Gradient::print();
    std::cout << "Type: LinearGradient\n";
    std::cout << "Point 1: " << p1.X << " " << p1.Y << "\n";
    std::cout << "Point 2: " << p2.X << " " << p2.Y << "\n";
}