#include "CircleRenderer.h"

CircleRenderer::CircleRenderer(const Fill& fill, const Stroke& stroke, const Circle& circle)
: Renderer(fill, stroke) {
    Gdiplus::Point coord = circle.getPoint();
    int r = circle.getRadius();

    x = coord.X - r;
    y = coord.Y - r;
    width = r * 2;
    height = r * 2;
}

void CircleRenderer::render(Gdiplus::Graphics& graphics) const {
    graphics.FillEllipse(brush, x, y, width, height);
    graphics.DrawEllipse(pen, x, y, width, height);
}
