#ifndef _TEXT_RENDERER_H
#define _TEXT_RENDERER_H

#include "Renderer.h"
#include <locale>
#include <codecvt>

class TextRenderer : public Renderer{

private:
    Gdiplus::GraphicsPath textGraphics;

public:
    TextRenderer(const Fill& fill, const Stroke& stroke, const Transform& transform, RawElement* rawElement);
    void render(Gdiplus::Graphics& graphics) const override;
};

#endif
