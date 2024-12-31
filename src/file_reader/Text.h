#ifndef _TEXT_H_
#define _TEXT_H_

#include "RawElement.h"

class Text : public RawElement {
private:
    std::string content;
    Gdiplus::PointF coord;
    double font_size;
    std::string font_family;
    std::string font_style;
    std::string text_anchor;
    std::string font_weight;
public:
    std::string getContent() const;
    Gdiplus::PointF getPoint() const;
    double getFontSize() const;
    std::string getFontFamily() const;
    std::string getFontStyle() const;
    std::string getFontWeight() const;
    std::string getTextAnchor() const;
    ElementType getType() const;
    void print() const override;
    Text(std::string content, Gdiplus::PointF coord, double font_size, 
        std::string font_family, std::string font_style, std::string font_weight,
        std::string text_anchor,
        const Stroke& stroke, const Fill& fill, const Transform& transform);
};

#endif