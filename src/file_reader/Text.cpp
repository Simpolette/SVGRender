#include "Text.h"

Text::Text(std::string content, Gdiplus::Point coord, int font_size, const Stroke& stroke, const Fill& fill)
: RawElement(stroke, fill) {
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