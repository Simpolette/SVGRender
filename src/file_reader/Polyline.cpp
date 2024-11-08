#include "Polyline.h"

PolyLine::PolyLine(std::string points, const Stroke& stroke, const Fill& fill)
: RawElement(stroke, fill) {
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

std::vector<Gdiplus::Point> PolyLine::getPoints() const {
    return points;
}

ElementType PolyLine::getType() const {
    return ElementType::POLYLINE;
}

