#include "Polygon.h"

PolyGon::PolyGon(std::string points, const Stroke& stroke, const Fill& fill, const Transform& transform)
: RawElement(stroke, fill, transform) {
    if (points != ""){
        std::istringstream iss(points);
        std::string temp;
        while (getline(iss, temp, ',')){
            int x = stoi(temp);
            getline(iss, temp, ' ');
            int y = stoi(temp);
            Gdiplus::Point coord(x, y);
            this->points.push_back(coord);
        }
    }
}

std::vector<Gdiplus::Point> PolyGon::getPoints() const {
    return points;
}

ElementType PolyGon::getType() const {
    return ElementType::POLYGON;
}

void PolyGon::print() const{
    std::cout << "Type: Polygon\n";
    RawElement::print();
    for (int i = 0; i < points.size(); i++){
        std::cout << "Point" << i + 1 << ": (" << points[i].X << ", " << points[i].Y << ")\n";
    }
}
