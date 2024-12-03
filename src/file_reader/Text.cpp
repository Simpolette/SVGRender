#include "Text.h"

Text::Text(std::string content, Gdiplus::Point coord, int font_size, const Stroke& stroke, const Fill& fill, const Transform& transform)
: RawElement(stroke, fill, transform) {
    this->content = content;
    this->coord = coord;
    this->font_size = font_size;
}

std::string Text::getContent() const {
    return content;
}

Gdiplus::Point Text::getPoint() const {
    return coord;
}

int Text::getFontSize() const {
    return font_size;
}

ElementType Text::getType() const {
    return ElementType::TEXT;
}

void Text::print() const{
    std::cout << "Type: Text\n";
    RawElement::print();
    std::cout << "Content: " << content << "\n";
    std::cout << "Bottom-left corner: (" << coord.X << ", " << coord.Y << ")\n";
    std::cout << "Font size: " << font_size << "\n";
}