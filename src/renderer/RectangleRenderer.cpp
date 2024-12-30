#include "RectangleRenderer.h"

RectangleRenderer::RectangleRenderer(const Fill& fill, const Stroke& stroke, const Transform& transform, RawElement* rawElement)
: Renderer(fill, stroke, transform) {
    Rectan* rect = dynamic_cast<Rectan*>(rawElement);
    Gdiplus::PointF coord = rect->getPoint();
    x = coord.X;
    y = coord.Y;
    width = rect->getWidth();
    height = rect->getHeight();

    Gdiplus::RectF bound(x, y, width, height);
    if (!brush){
        brush = fill.getGradientBrush(bound);
    }
}

void RectangleRenderer::render(Gdiplus::Graphics& graphics) const {
    Gdiplus::Matrix originalMatrix;
    graphics.GetTransform(&originalMatrix);
    graphics.MultiplyTransform(matrix);
    
    graphics.DrawRectangle(pen, x, y, width, height);
    graphics.FillRectangle(brush, x, y, width, height);

    graphics.SetTransform(&originalMatrix);
}
