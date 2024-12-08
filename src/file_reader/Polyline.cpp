#include "Polyline.h"

PolyLine::PolyLine(std::string points, const Stroke& stroke, const Fill& fill, const Transform& transform)
: RawElement(stroke, fill, transform) {
    if (points != ""){
        std::istringstream iss(points);
        double x, y;
        while (iss >> x){
            iss >> y;
            Gdiplus::PointF coord(x, y);
            this->points.push_back(coord);
        }
    }
}

std::vector<Gdiplus::PointF> PolyLine::getPoints() const {
    return points;
}

ElementType PolyLine::getType() const {
    return ElementType::POLYLINE;
}

void PolyLine::print() const{
    std::cout << "Type: Polyline\n";
    RawElement::print();
    for (int i = 0; i < points.size(); i++){
        std::cout << "Point" << i + 1 << ": (" << points[i].X << ", " << points[i].Y << ")\n";
    }
}
