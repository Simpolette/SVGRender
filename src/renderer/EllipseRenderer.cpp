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
    Gdiplus::PathGradientBrush* radialBrush = dynamic_cast< Gdiplus::PathGradientBrush* >(brush);
    if (radialBrush){
        int colorCount = radialBrush->GetInterpolationColorCount();
        Gdiplus::Color* colors = new Gdiplus::Color[colorCount];
        Gdiplus::REAL* offset = new Gdiplus::REAL[colorCount];
        radialBrush->GetInterpolationColors(colors, offset, colorCount);
        Gdiplus::Color excludeColor = colors[colorCount - 1];
        Gdiplus::SolidBrush fillExclude(excludeColor);
        graphics.FillEllipse(&fillExclude, x, y, width, height);
        delete colors;
    }
    
    graphics.FillEllipse(brush, x, y, width, height);
    graphics.DrawEllipse(pen, x, y, width, height);

    graphics.SetTransform(&originalMatrix);
}
