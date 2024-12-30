#ifndef _CIRCLE_RENDERER_H_
#define _CIRCLE_RENDERER_H_

#include "Renderer.h"

class CircleRenderer : public Renderer {

private:
    Gdiplus::REAL x;
    Gdiplus::REAL y;
    Gdiplus::REAL width;
    Gdiplus::REAL height;

public:
    CircleRenderer(const Fill& fill, const Stroke& stroke, const Transform& transform, RawElement* rawElement);
    void render(Gdiplus::Graphics& graphics) const override;

};

#endif