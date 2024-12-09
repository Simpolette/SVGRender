#ifndef _PATH_RENDERER_H_
#define _PATH_RENDERER_H_

#include "Renderer.h"

class PathRenderer : public Renderer {

private:
    Gdiplus::GraphicsPath pathGraphics;
public:
    PathRenderer(const Fill& fill, const Stroke& stroke, const Transform& transform, const Path& path);
    void render(Gdiplus::Graphics& graphics) const override;
};

#endif