#ifndef _FACTORY_RENDERER_H_
#define _FACTORY_RENDERER_H_

#include "Renderer.h"
#include "LineRenderer.h"
#include "PolylineRenderer.h"
#include "PolygonRenderer.h"
#include "RectangleRenderer.h"
#include "CircleRenderer.h"
#include "EllipseRenderer.h"
#include "TextRenderer.h"


class RendererFactory{

public:
    static Renderer* createRenderer(RawElement* rawElement);

};

#endif