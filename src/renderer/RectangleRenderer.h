#ifndef _RECTANGLE_RENDER_H_
#define _RECTANGLE_RENDER_H_

#include "Renderer.h"

class RectangleRenderer : public Renderer {

private:
    Gdiplus::REAL x;
    Gdiplus::REAL y;
    Gdiplus::REAL width;
    Gdiplus::REAL height;

public:
    RectangleRenderer(const Fill& fill, const Stroke& stroke, const Transform& transform, const Rectan& rect);
    void render(Gdiplus::Graphics& graphics) const override;
};

#endif