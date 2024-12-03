#ifndef _PATH_H_
#define _PATH_H_

#include <vector>

#include "RawElement.h"

class Path : public RawElement {
private:
    std::vector<std::pair<char, Gdiplus::Point>> table;
public:
    ElementType getType() const;
    std::vector<std::pair<char, Gdiplus::Point>> getPath() const;
    void print() const override;
    Path(const std::vector<std::pair<char, Gdiplus::Point>> &tab, const Stroke& stroke, const Fill& fill, const Transform& transform);
};

#endif