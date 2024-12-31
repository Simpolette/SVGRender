#include "PolylineRenderer.h"

PolylineRenderer::PolylineRenderer(const Fill& fill, const Stroke& stroke, const Transform& transform, RawElement* rawElement)
: Renderer(fill, stroke, transform) {
    PolyLine* polyline = dynamic_cast<PolyLine*>(rawElement);
    std::vector<Gdiplus::PointF> pointsVec = polyline->getPoints();
    count = pointsVec.size();
    points = new Gdiplus::PointF[count];
    
    Gdiplus::REAL minX, minY, maxX, maxY;
    if (count > 0){
        minX = maxX = pointsVec[0].X;
        minY = maxY = pointsVec[0].Y;
    }

    for (int i = 0; i < count; i++){
        points[i] = pointsVec[i];

        minX = std::min(minX, points[i].X);
        minY = std::min(minY, points[i].Y);
        maxX = std::max(maxX, points[i].X);
        maxY = std::max(maxY, points[i].Y);
    }

    Gdiplus::RectF bound(minX, minY, maxX - minX, maxY - minY);
    if (!brush){
        brush = fill.getGradientBrush(bound);
    }
}

void PolylineRenderer::render(Gdiplus::Graphics& graphics) const {

    Gdiplus::Matrix originalMatrix;
    graphics.GetTransform(&originalMatrix);
    graphics.MultiplyTransform(matrix);
 
    Gdiplus::GraphicsPath polyline;
    polyline.StartFigure();
    polyline.AddLines(points, count);

    graphics.FillPath(brush, &polyline);
    graphics.DrawPath(pen, &polyline);

    graphics.SetTransform(&originalMatrix);
}

PolylineRenderer::~PolylineRenderer(){
    delete[] points;
}