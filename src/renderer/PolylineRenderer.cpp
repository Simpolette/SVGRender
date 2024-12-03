#include "PolylineRenderer.h"

PolylineRenderer::PolylineRenderer(const Fill& fill, const Stroke& stroke, const Transform& transform, const PolyLine& polyline)
: Renderer(fill, stroke, transform) {
    std::vector<Gdiplus::Point> pointsVec = polyline.getPoints();
    count = pointsVec.size();
    points = new Gdiplus::Point[count];
    for (int i = 0; i < count; i++){
        points[i] = pointsVec[i];
    }
}

void PolylineRenderer::render(Gdiplus::Graphics& graphics) const {
    Gdiplus::GraphicsPath polyline;
    polyline.StartFigure();
    polyline.AddLines(points, count);

    graphics.FillPath(brush, &polyline);
    graphics.DrawPath(pen, &polyline);
}

PolylineRenderer::~PolylineRenderer(){
    delete[] points;
}