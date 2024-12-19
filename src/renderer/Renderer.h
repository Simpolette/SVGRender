#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <Windows.h>
#include <Gdiplus.h>
#include <objidl.h>
#include <sstream>
#include "../file_reader/SVG.h"

#pragma comment (lib, "Gdiplus.lib")

class Renderer{

protected:
    Gdiplus::Pen* pen;
    Gdiplus::Brush* brush;
    Gdiplus::Matrix* matrix;

    Gdiplus::Pen* getPen(const Stroke& stroke);
    Gdiplus::Brush* getBrush(const Fill& fill);
    Gdiplus::Matrix* getMatrix(const Transform& transform);

public:
    Renderer(const Fill& fill, const Stroke& stroke, const Transform& transform);
    virtual void render(Gdiplus::Graphics& graphics) const = 0;
    virtual ~Renderer();
};

#endif