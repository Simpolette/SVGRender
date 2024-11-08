#ifndef _ELLIPSE_RENDERER_H_
#define _ELLIPSE_RENDERER_H_

#include "Renderer.h"

class EllipseRenderer : public Renderer {

private:
    int x;
    int y;
    int width;
    int height;

public:
    EllipseRenderer(const Fill& fill, const Stroke& stroke, const Ellip& ellipse);
    void render(Gdiplus::Graphics& graphics) const override;
};

#endif