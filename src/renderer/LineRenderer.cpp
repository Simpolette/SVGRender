#include "LineRenderer.h"

LineRenderer::LineRenderer(const Fill& fill, const Stroke& stroke, const Transform& transform, const Line& line)
: Renderer(fill, stroke, transform) {
    startPoint = line.getPointStart();
    endPoint = line.getPointEnd();
}

void LineRenderer::render(Gdiplus::Graphics& graphics) const {
    Gdiplus::Matrix originalMatrix;
    graphics.GetTransform(&originalMatrix);
    graphics.MultiplyTransform(matrix);

    graphics.DrawLine(pen, startPoint, endPoint);

    graphics.SetTransform(&originalMatrix);
}
