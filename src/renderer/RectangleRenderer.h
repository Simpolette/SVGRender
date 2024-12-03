#ifndef _RECTANGLE_RENDER_H_
#define _RECTANGLE_RENDER_H_

#include "Renderer.h"

class RectangleRenderer : public Renderer {

private:
    int x;
    int y;
    int width;
    int height;

public:
    RectangleRenderer(const Fill& fill, const Stroke& stroke, const Transform& transform, const Rectan& rect);
    void render(Gdiplus::Graphics& graphics) const override;
};

#endif