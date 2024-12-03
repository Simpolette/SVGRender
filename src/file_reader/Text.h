#ifndef _TEXT_H_
#define _TEXT_H_

#include "RawElement.h"

class Text : public RawElement {
private:
    std::string content;
    Gdiplus::Point coord;
    int font_size;
public:
    std::string getContent() const;
    Gdiplus::Point getPoint() const;
    int getFontSize() const;
    ElementType getType() const;
    void print() const override;
    Text(std::string content, Gdiplus::Point coord, int font_size, const Stroke& stroke, const Fill& fill, const Transform& transform);
};

#endif