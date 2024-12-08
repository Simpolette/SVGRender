#include "CircleRenderer.h"

CircleRenderer::CircleRenderer(const Fill& fill, const Stroke& stroke, const Transform& transform, const Circle& circle)
: Renderer(fill, stroke, transform) {
    Gdiplus::PointF coord = circle.getPoint();
    int r = circle.getRadius();

    x = coord.X - r;
    y = coord.Y - r;
    width = r * 2;
    height = r * 2;
}

void CircleRenderer::render(Gdiplus::Graphics& graphics) const {
    Gdiplus::Matrix originalMatrix;
    graphics.GetTransform(&originalMatrix);
    graphics.MultiplyTransform(matrix);

    graphics.FillEllipse(brush, x, y, width, height);
    graphics.DrawEllipse(pen, x, y, width, height);

    graphics.SetTransform(&originalMatrix);
}
