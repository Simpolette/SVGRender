#include "PolygonRenderer.h"

PolygonRenderer::PolygonRenderer(const Fill& fill, const Stroke& stroke, const PolyGon& polygon)
: Renderer(fill, stroke) {
    std::vector<Gdiplus::Point> pointsVec = polygon.getPoints();
    count = pointsVec.size();
    points = new Gdiplus::Point[count];
    for (int i = 0; i < count; i++){
        points[i] = pointsVec[i];
    }
}

void PolygonRenderer::render(Gdiplus::Graphics& graphics) const {
    graphics.FillPolygon(brush, points, count);
    graphics.DrawPolygon(pen, points, count);
}

PolygonRenderer::~PolygonRenderer(){
    delete[] points;
}

