#ifndef _LINE_RENDERER_H_
#define _LINE_RENDERER_H_

#include "Renderer.h"

class LineRenderer : public Renderer {

private:
    Gdiplus::Point startPoint;
    Gdiplus::Point endPoint;

public:
    LineRenderer(const Fill& fill, const Stroke& stroke, const Transform& transform, const Line& line);
    void render(Gdiplus::Graphics& graphics) const override;
};

#endif