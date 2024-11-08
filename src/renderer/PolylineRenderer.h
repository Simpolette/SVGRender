#ifndef _POLYLINE_RENDERER_H_
#define _POLYLINE_RENDERER_H_

#include "Renderer.h"

class PolylineRenderer : public Renderer {

private:
    Gdiplus::Point* points;
    int count;

public:
    PolylineRenderer(const Fill& fill, const Stroke& stroke, const PolyLine& polyline);
    void render(Gdiplus::Graphics& graphics) const override;
    ~PolylineRenderer();
};

#endif