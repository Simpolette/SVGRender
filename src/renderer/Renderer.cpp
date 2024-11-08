#include "Renderer.h"
using namespace std;
Renderer::Renderer(const Fill& fill, const Stroke& stroke){
    pen = getPen(stroke);
    brush = getBrush(fill);
}

Gdiplus::Pen* Renderer::getPen(const Stroke& stroke) {
    Gdiplus::Color color = stroke.getColorA();
    cout << stroke.getOpacity() * 255 << " " << (int)color.GetR() << " " << (int)color.GetG() << " " << (int)color.GetB() << endl;
    Gdiplus::Color penColor(
        static_cast<BYTE>(stroke.getOpacity() * 255), // Độ trong suốt (alpha)
        color.GetRed(),
        color.GetGreen(),
        color.GetBlue()
    );

    Gdiplus::Pen* pen = new Gdiplus::Pen(penColor, static_cast<Gdiplus::REAL>(stroke.getWidth()));
    
    return pen;
}

Gdiplus::Brush* Renderer::getBrush(const Fill& fill) {
    Gdiplus::Color color = fill.getColorA();
    cout << fill.getOpacity() * 255 << " " << (int)color.GetR() << " " << (int)color.GetG() << " " << (int)color.GetB() << endl;
    Gdiplus::Color brushColor(
        static_cast<BYTE>(fill.getOpacity() * 255), 
        color.GetRed(),
        color.GetGreen(),
        color.GetBlue()
    );

    Gdiplus::Brush* brush = new Gdiplus::SolidBrush(brushColor);    

    return brush;
}