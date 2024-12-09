#include "Text.h"

Text::Text(std::string content, Gdiplus::PointF coord, double font_size, 
        std::string font_family, std::string font_style, std::string text_anchor,
        const Stroke& stroke, const Fill& fill, const Transform& transform)
: RawElement(stroke, fill, transform) {
    this->content = content;
    this->coord = coord;
    this->font_size = font_size;
    this->font_family = font_family;
    this->font_style = font_style;
    this->text_anchor = text_anchor;
}

std::string Text::getContent() const {
    return content;
}

Gdiplus::PointF Text::getPoint() const {
    return coord;
}

double Text::getFontSize() const {
    return font_size;
}

std::string Text::getFontFamily() const {
    return font_family;
}

std::string Text::getFontStyle() const {
    return font_style;
}

std::string Text::getTextAnchor() const {
    return text_anchor;
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
    std::cout << "Font family: " << font_family << "\n"; 
}