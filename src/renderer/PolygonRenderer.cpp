#include "PolygonRenderer.h"

PolygonRenderer::PolygonRenderer(const Fill& fill, const Stroke& stroke, const Transform& transform, RawElement* rawElement)
: Renderer(fill, stroke, transform) {
    PolyGon* polygon = dynamic_cast<PolyGon*>(rawElement);
    std::vector<Gdiplus::PointF> pointsVec = polygon->getPoints();
    count = pointsVec.size();
    points = new Gdiplus::PointF[count];
    
    Gdiplus::REAL minX, minY, maxX, maxY;
    if (count > 0){
        minX = maxX = points[0].X;
        minY = maxY = points[0].Y;
    }

    for (int i = 0; i < count; i++){
        minX = std::min(minX, points[i].X);
        minY = std::min(minY, points[i].Y);
        maxX = std::max(maxX, points[i].X);
        maxY = std::max(maxY, points[i].Y);

        points[i] = pointsVec[i];
    }

    Gdiplus::RectF bound(minX, minY, maxX - minX, maxY - minY);
    if (!brush){
        brush = fill.getGradientBrush(bound);
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

