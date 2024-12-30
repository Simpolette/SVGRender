#ifndef _POLYLINE_RENDERER_H_
#define _POLYLINE_RENDERER_H_

#include "Renderer.h"

class PolylineRenderer : public Renderer {

private:
    Gdiplus::PointF* points;
    int count;

public:
    PolylineRenderer(const Fill& fill, const Stroke& stroke, const Transform& transform, RawElement* rawElement);
    void render(Gdiplus::Graphics& graphics) const override;
    ~PolylineRenderer();
};

#endif