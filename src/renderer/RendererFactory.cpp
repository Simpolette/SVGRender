#include "RendererFactory.h"

Renderer* RendererFactory::createRenderer(RawElement* rawElement){
    Fill fill = rawElement->getFill();
    Stroke stroke = rawElement->getStroke();
    Transform transform = rawElement->getTransform();

    switch (rawElement->getType()){
        case ElementType::LINE:{
            Line* line = dynamic_cast<Line*>(rawElement);
            return new LineRenderer(fill, stroke, transform, *line);
        }
        case ElementType::POLYLINE:{
            PolyLine* polyline = dynamic_cast<PolyLine*>(rawElement);
            return new PolylineRenderer(fill, stroke, transform, *polyline);
        }
        case ElementType::POLYGON:{
            PolyGon* polygon = dynamic_cast<PolyGon*>(rawElement);
            return new PolygonRenderer(fill, stroke, transform, *polygon);
        }
        case ElementType::RECTANGLE:{
            Rectan* rect = dynamic_cast<Rectan*>(rawElement);
            return new RectangleRenderer(fill, stroke, transform, *rect);
        }
        case ElementType::CIRCLE:{
            Circle* circle = dynamic_cast<Circle*>(rawElement);
            return new CircleRenderer(fill, stroke, transform, *circle);
        }
        case ElementType::ELLIPSE:{
            Ellip* ellipse = dynamic_cast<Ellip*>(rawElement);
            return new EllipseRenderer(fill, stroke, transform, *ellipse);        
        }
        case ElementType::TEXT:{
            Text* text = dynamic_cast<Text*>(rawElement);
            return new TextRenderer(fill, stroke, transform, *text);
        }
        case ElementType::GROUP:{
            Group* group = dynamic_cast<Group*>(rawElement);
            return new GroupRenderer(fill, stroke, transform, *group);
        }
        case ElementType::PATH:{
            Path* path = dynamic_cast<Path*>(rawElement);
            return new PathRenderer(fill, stroke, transform, *path);
        }
        default:
            return NULL;
    } 
}
