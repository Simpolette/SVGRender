#include "CircleRenderer.h"

CircleRenderer::CircleRenderer(const Fill& fill, const Stroke& stroke, const Transform& transform, RawElement* rawElement)
: Renderer(fill, stroke, transform) {
    Circle* circle = dynamic_cast<Circle*>(rawElement);
    Gdiplus::PointF coord = circle->getPoint();
    double r = circle->getRadius();

    x = coord.X - r;
    y = coord.Y - r;
    width = r * 2;
    height = r * 2;

    Gdiplus::RectF bound(x, y, width, height);
    if (!brush){
        brush = fill.getGradientBrush(bound);
    }
}

void CircleRenderer::render(Gdiplus::Graphics& graphics) const {
    Gdiplus::Matrix originalMatrix;
    graphics.GetTransform(&originalMatrix);
    graphics.MultiplyTransform(matrix);

    graphics.FillEllipse(brush, x, y, width, height);
    graphics.DrawEllipse(pen, x, y, width, height);

    graphics.SetTransform(&originalMatrix);
}
