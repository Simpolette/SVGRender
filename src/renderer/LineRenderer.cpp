#include "LineRenderer.h"

LineRenderer::LineRenderer(const Fill& fill, const Stroke& stroke, const Transform& transform, RawElement* rawElement)
: Renderer(fill, stroke, transform) {
    Line* line = dynamic_cast<Line*>(rawElement);
    startPoint = line->getPointStart();
    endPoint = line->getPointEnd();
}

void LineRenderer::render(Gdiplus::Graphics& graphics) const {
    Gdiplus::Matrix originalMatrix;
    graphics.GetTransform(&originalMatrix);
    graphics.MultiplyTransform(matrix);

    graphics.DrawLine(pen, startPoint, endPoint);

    graphics.SetTransform(&originalMatrix);
}
