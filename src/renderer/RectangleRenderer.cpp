#include "RectangleRenderer.h"

RectangleRenderer::RectangleRenderer(const Fill& fill, const Stroke& stroke, const Rectan& rect)
: Renderer(fill, stroke) {
    Gdiplus::Point coord = rect.getPoint();
    x = coord.X;
    y = coord.Y;
    width = rect.getWidth();
    height = rect.getHeight();
}

void RectangleRenderer::render(Gdiplus::Graphics& graphics) const {
    graphics.DrawRectangle(pen, x, y, width, height);
    graphics.FillRectangle(brush, x, y, width, height);
}
