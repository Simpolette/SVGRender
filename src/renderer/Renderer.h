#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <Windows.h>
#include <Gdiplus.h>
#include <objidl.h>
#include "../file_reader/SVG.h"

#pragma comment (lib, "Gdiplus.lib")

class Renderer{

protected:
    Gdiplus::Pen* pen;
    Gdiplus::Brush* brush;

    Gdiplus::Pen* getPen(const Stroke& stroke);
    Gdiplus::Brush* getBrush(const Fill& fill);

public:
    Renderer(const Fill& fill, const Stroke& stroke);
    virtual void render(Gdiplus::Graphics& graphics) const = 0;

};

#endif