#ifndef _PATH_RENDERER_H_
#define _PATH_RENDERER_H_

#include "Renderer.h"

#ifndef DEGREE
#ifndef PI
#define PI 3.14159265358979323846 // Định nghĩa lại nếu chưa có
#endif  
#define DEGREE (180 / PI)
#endif

class PathRenderer : public Renderer {

private:
    Gdiplus::GraphicsPath pathGraphics;

private:
    float CalculateVectorAngle(float x, float y) const;

public:
    PathRenderer(const Fill& fill, const Stroke& stroke, const Transform& transform, RawElement* rawElement);
    void render(Gdiplus::Graphics& graphics) const override;
    
};

#endif