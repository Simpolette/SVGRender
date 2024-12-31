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
    Gdiplus::PathGradientBrush* radialBrush = dynamic_cast< Gdiplus::PathGradientBrush* >(brush);
    if (radialBrush){
        int colorCount = radialBrush->GetInterpolationColorCount();
        Gdiplus::Color* colors = new Gdiplus::Color[colorCount];
        Gdiplus::REAL* offset = new Gdiplus::REAL[colorCount];
        radialBrush->GetInterpolationColors(colors, offset, colorCount);
        Gdiplus::Color excludeColor = colors[colorCount - 1];
        Gdiplus::SolidBrush fillExclude(excludeColor);
        graphics.FillRectangle(&fillExclude, x, y, width, height);
        delete colors;
    }
    graphics.FillRectangle(brush, x, y, width, height);
    graphics.DrawRectangle(pen, x, y, width, height);

    graphics.SetTransform(&originalMatrix);
}
