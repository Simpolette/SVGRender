#include "Path.h"

Path::Path(const std::vector<std::pair<char, Gdiplus::PointF    >> &tab, const Stroke& stroke, const Fill& fill, const Transform& transform)
:   RawElement(stroke, fill, transform) {
    this->table = tab;
}

ElementType Path::getType() const {
    return ElementType::PATH;
}

std::vector<std::pair<char, Gdiplus::PointF >> Path::getPath() const {
    return table;
}

void Path::print() const{
    std::cout << "Type: Path\n";
    RawElement::print();
    for (int i = 0; i < table.size(); i++){
        std::cout << "Command: " << table[i].first << "\n";
        std::cout << "Point: (" << table[i].second.X << ", " << table[i].second.Y << ")\n";
    }
}