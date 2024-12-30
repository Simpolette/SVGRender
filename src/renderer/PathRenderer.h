#ifndef _PATH_RENDERER_H_
#define _PATH_RENDERER_H_

#include "Renderer.h"

class PathRenderer : public Renderer {

private:
    Gdiplus::GraphicsPath pathGraphics;

private:
    float CalculateVectorAngle(float x, float y) const;

public:
    PathRenderer(const Fill& fill, const Stroke& stroke, const Transform& transform, RawElement* rawElement);
    void render(Gdiplus::Graphics& graphics) const override;
    
};

#endif