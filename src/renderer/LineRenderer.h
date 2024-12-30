#ifndef _LINE_RENDERER_H_
#define _LINE_RENDERER_H_

#include "Renderer.h"

class LineRenderer : public Renderer {

private:
    Gdiplus::PointF startPoint;
    Gdiplus::PointF endPoint;

public:
    LineRenderer(const Fill& fill, const Stroke& stroke, const Transform& transform, RawElement* rawElement);
    void render(Gdiplus::Graphics& graphics) const override;
};

#endif