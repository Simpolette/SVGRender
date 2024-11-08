#include "RendererFactory.h"

Renderer* RendererFactory::createRenderer(RawElement* rawElement){
    Fill fill = rawElement->getFill();
    Stroke stroke = rawElement->getStroke();
    
    switch (rawElement->getType()){
        case ElementType::LINE:{
            Line* line = dynamic_cast<Line*>(rawElement);
            return new LineRenderer(fill, stroke, *line);
        }
        case ElementType::POLYLINE:{
            PolyLine* polyline = dynamic_cast<PolyLine*>(rawElement);
            return new PolylineRenderer(fill, stroke, *polyline);
        }
        case ElementType::POLYGON:{
            PolyGon* polygon = dynamic_cast<PolyGon*>(rawElement);
            return new PolygonRenderer(fill, stroke, *polygon);
        }
        case ElementType::RECTANGLE:{
            Rectan* rect = dynamic_cast<Rectan*>(rawElement);
            return new RectangleRenderer(fill, stroke, *rect);
        }
        case ElementType::CIRCLE:{
            Circle* circle = dynamic_cast<Circle*>(rawElement);
            return new CircleRenderer(fill, stroke, *circle);
        }
        case ElementType::ELLIPSE:{
            Ellip* ellipse = dynamic_cast<Ellip*>(rawElement);
            return new EllipseRenderer(fill, stroke, *ellipse);        
        }
        case ElementType::TEXT:{
            Text* text = dynamic_cast<Text*>(rawElement);
            return new TextRenderer(fill, stroke, *text);
        }
        default:
            return NULL;
    } 
}
