#include "EllipseRenderer.h"

EllipseRenderer::EllipseRenderer(const Fill& fill, const Stroke& stroke, const Transform& transform, const Ellip& ellipse)
: Renderer(fill, stroke, transform) {
    Gdiplus::PointF coord = ellipse.getPoint();
    int rx = ellipse.getRX();
    int ry = ellipse.getRY();

    x = coord.X - rx;
    y = coord.Y - ry;
    width = rx * 2;
    height = ry * 2;
}

void EllipseRenderer::render(Gdiplus::Graphics& graphics) const {
    Gdiplus::Matrix originalMatrix;
    graphics.GetTransform(&originalMatrix);
    graphics.MultiplyTransform(matrix);

    
    graphics.FillEllipse(brush, x, y, width, height);
    graphics.DrawEllipse(pen, x, y, width, height);

    graphics.SetTransform(&originalMatrix);
}
