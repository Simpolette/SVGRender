#include "EllipseRenderer.h"

EllipseRenderer::EllipseRenderer(const Fill& fill, const Stroke& stroke, const Ellip& ellipse)
: Renderer(fill, stroke) {
    Gdiplus::Point coord = ellipse.getPoint();
    int rx = ellipse.getRX();
    int ry = ellipse.getRY();

    x = coord.X - rx;
    y = coord.Y - ry;
    width = rx * 2;
    height = ry * 2;
}

void EllipseRenderer::render(Gdiplus::Graphics& graphics) const {
    graphics.FillEllipse(brush, x, y, width, height);
    graphics.DrawEllipse(pen, x, y, width, height);
}
