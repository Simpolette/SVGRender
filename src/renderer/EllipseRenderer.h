#ifndef _ELLIPSE_RENDERER_H_
#define _ELLIPSE_RENDERER_H_

#include "Renderer.h"

class EllipseRenderer : public Renderer {

private:
    Gdiplus::REAL x;
    Gdiplus::REAL y;
    Gdiplus::REAL width;
    Gdiplus::REAL height;

public:
    EllipseRenderer(const Fill& fill, const Stroke& stroke, const Transform& transform, RawElement* rawElement);
    void render(Gdiplus::Graphics& graphics) const override;
};

#endif