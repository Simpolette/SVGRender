#include "EllipseRenderer.h"

EllipseRenderer::EllipseRenderer(const Fill& fill, const Stroke& stroke, const Transform& transform, RawElement* rawElement)
: Renderer(fill, stroke, transform) {
    Ellip* ellipse = dynamic_cast<Ellip*>(rawElement);
    Gdiplus::PointF coord = ellipse->getPoint();
    double rx = ellipse->getRX();
    double ry = ellipse->getRY();

    x = coord.X - rx;
    y = coord.Y - ry;
    width = rx * 2;
    height = ry * 2;

    Gdiplus::RectF bound(x, y, width, height);
    if (!brush){
        brush = fill.getGradientBrush(bound);
    }
}

void EllipseRenderer::render(Gdiplus::Graphics& graphics) const {
    Gdiplus::Matrix originalMatrix;
    graphics.GetTransform(&originalMatrix);
    graphics.MultiplyTransform(matrix);

    
    graphics.FillEllipse(brush, x, y, width, height);
    graphics.DrawEllipse(pen, x, y, width, height);

    graphics.SetTransform(&originalMatrix);
}
