#ifndef _TEXT_RENDERER_H
#define _TEXT_RENDERER_H

#include "Renderer.h"
#include <locale>
#include <codecvt>

class TextRenderer : public Renderer{

private:
    std::wstring content;
    int length;
    Gdiplus::FontFamily* family;
    int style;
    Gdiplus::REAL emSize;
    Gdiplus::PointF origin;
    Gdiplus::StringFormat format;

public:
    TextRenderer(const Fill& fill, const Stroke& stroke, const Transform& transform, const Text& text);
    void render(Gdiplus::Graphics& graphics) const override;
    ~TextRenderer();
};

#endif
