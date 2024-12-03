#include "LineRenderer.h"

LineRenderer::LineRenderer(const Fill& fill, const Stroke& stroke, const Transform& transform, const Line& line)
: Renderer(fill, stroke, transform) {
    startPoint = line.getPointStart();
    endPoint = line.getPointEnd();
}

void LineRenderer::render(Gdiplus::Graphics& graphics) const {
    graphics.DrawLine(pen, startPoint, endPoint);
}
