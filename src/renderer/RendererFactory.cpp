#include "RendererFactory.h"

Renderer* RendererFactory::createRenderer(RawElement* rawElement){
    if (!rawElement){
        return nullptr;
    }
    Fill fill = rawElement->getFill();
    Stroke stroke = rawElement->getStroke();
    Transform transform = rawElement->getTransform();

    switch (rawElement->getType()){
        case ElementType::LINE:{
            return new LineRenderer(fill, stroke, transform, rawElement);
        }
        case ElementType::POLYLINE:{
            return new PolylineRenderer(fill, stroke, transform, rawElement);
        }
        case ElementType::POLYGON:{
            return new PolygonRenderer(fill, stroke, transform, rawElement);
        }
        case ElementType::RECTANGLE:{
            return new RectangleRenderer(fill, stroke, transform, rawElement);
        }
        case ElementType::CIRCLE:{
            return new CircleRenderer(fill, stroke, transform, rawElement);
        }
        case ElementType::ELLIPSE:{
            return new EllipseRenderer(fill, stroke, transform, rawElement);        
        }
        case ElementType::TEXT:{
            return new TextRenderer(fill, stroke, transform, rawElement);
        }
        case ElementType::GROUP:{
            return new GroupRenderer(fill, stroke, transform, rawElement);
        }
        case ElementType::PATH:{
            return new PathRenderer(fill, stroke, transform, rawElement);
        }
        default:
            return NULL;
    } 
}
