#include "Renderer.h"
using namespace std;
Renderer::Renderer(const Fill& fill, const Stroke& stroke, const Transform& transform){
    pen = getPen(stroke);
    brush = getBrush(fill);
    matrix = getMatrix(transform);
}

Gdiplus::Pen* Renderer::getPen(const Stroke& stroke) {
    Gdiplus::Color color = stroke.getColorA();
    Gdiplus::Color penColor(
        static_cast<BYTE>(stroke.getOpacity() * 255), // Độ trong suốt (alpha)
        color.GetRed(),
        color.GetGreen(),
        color.GetBlue()
    );

    Gdiplus::Pen* pen = new Gdiplus::Pen(penColor, static_cast<Gdiplus::REAL>(stroke.getWidth()));
    
    pen->SetLineJoin(Gdiplus::LineJoinMiter);
    pen->SetMiterLimit(stroke.getMiterLimit());

    return pen;
}

Gdiplus::Brush* Renderer::getBrush(const Fill& fill) {
    Gdiplus::Color color = fill.getColorA();
    Gdiplus::Color brushColor(
        static_cast<BYTE>(fill.getOpacity() * 255), 
        color.GetRed(),
        color.GetGreen(),
        color.GetBlue()
    );

    Gdiplus::Brush* brush = new Gdiplus::SolidBrush(brushColor);    

    return brush;
}

Gdiplus::Matrix* Renderer::getMatrix(const Transform& transform){
    Gdiplus::Matrix* matrix = new Gdiplus::Matrix;
    matrix->Translate(transform.getTranslate().X, transform.getTranslate().Y);
    matrix->Scale(transform.getScale().X, transform.getScale().Y);
    matrix->Rotate(transform.getRotate());

    return matrix;
}

Renderer::~Renderer(){
    delete pen;
    delete brush;
    delete matrix;
}