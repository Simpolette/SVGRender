#ifndef _POLYGON_RENDERER_H_
#define _POLYGON_RENDERER_H_

#include "Renderer.h"

class PolygonRenderer : public Renderer {

private:
    Gdiplus::PointF* points;
    int count;

public:
    PolygonRenderer(const Fill& fill, const Stroke& stroke, const Transform& transform, const PolyGon& polygon);
    void render(Gdiplus::Graphics& graphics) const override;
    ~PolygonRenderer();
};

#endif