#ifndef _CIRCLE_RENDERER_H_
#define _CIRCLE_RENDERER_H_

#include "EllipseRenderer.h"

class CircleRenderer : public Renderer {

private:
    int x;
    int y;
    int width;
    int height;

public:
    CircleRenderer(const Fill& fill, const Stroke& stroke, const Circle& circle);
    void render(Gdiplus::Graphics& graphics) const override;

};

#endif