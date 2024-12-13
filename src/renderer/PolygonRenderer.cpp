#include "PolygonRenderer.h"

PolygonRenderer::PolygonRenderer(const Fill& fill, const Stroke& stroke, const Transform& transform, const PolyGon& polygon)
: Renderer(fill, stroke, transform) {
    std::vector<Gdiplus::PointF> pointsVec = polygon.getPoints();
    count = pointsVec.size();
    points = new Gdiplus::PointF[count];
    for (int i = 0; i < count; i++){
        points[i] = pointsVec[i];
    }
}

void PolygonRenderer::render(Gdiplus::Graphics& graphics) const {
    
    Gdiplus::Matrix originalMatrix;
    graphics.GetTransform(&originalMatrix);
    graphics.MultiplyTransform(matrix);
    
    Gdiplus::GraphicsPath polygon;
    polygon.StartFigure();
    polygon.AddPolygon(points, count);
    polygon.SetFillMode(Gdiplus::FillModeWinding);

    graphics.FillPath(brush, &polygon);
    graphics.DrawPath(pen, &polygon);

    graphics.SetTransform(&originalMatrix);
}

PolygonRenderer::~PolygonRenderer(){
    delete[] points;
}

