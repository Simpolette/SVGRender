#ifndef _PATH_H_
#define _PATH_H_

#include <vector>

#include "RawElement.h"

class Path : public RawElement {
private:
    std::vector<std::pair<char, Gdiplus::PointF>> table;
public:
    ElementType getType() const;
    std::vector<std::pair<char, Gdiplus::PointF>> getPath() const;
    void print() const override;
    Path(const std::vector<std::pair<char, Gdiplus::PointF>> &tab, const Stroke& stroke, const Fill& fill, const Transform& transform);
};

#endif