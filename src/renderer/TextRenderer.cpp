#include "TextRenderer.h"

TextRenderer::TextRenderer(const Fill& fill, const Stroke& stroke, const Transform& transform, const Text& text) 
: Renderer(fill, stroke, transform) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    family = new Gdiplus::FontFamily(converter.from_bytes(text.getFontFamily()).c_str());
    if (family->GetLastStatus() != Gdiplus::Ok){
        delete family;
        family = new Gdiplus::FontFamily(L"Times New Roman");
    }

    double ascent = family->GetCellAscent(0);
    double emHeight = family->GetEmHeight(0);
    Gdiplus::PointF point = text.getPoint();

    content = converter.from_bytes(text.getContent());
    length = content.size();
    style = 0;
    emSize = (float)text.getFontSize();
    double ascentOffset = emSize * (static_cast<Gdiplus::REAL>(ascent) / emHeight);
    double topLeftY = point.Y - ascentOffset;

    origin = Gdiplus::PointF(point.X, topLeftY);
    format.SetAlignment(Gdiplus::StringAlignmentNear);
}

void TextRenderer::render(Gdiplus::Graphics& graphics) const{
    Gdiplus::Matrix originalMatrix;
    graphics.GetTransform(&originalMatrix);
    graphics.MultiplyTransform(matrix);

    
    Gdiplus::GraphicsPath text;
    text.StartFigure();
    text.AddString(content.c_str(), length, family, style, emSize, origin, &format);

    graphics.FillPath(brush, &text);
    graphics.DrawPath(pen, &text);

    graphics.SetTransform(&originalMatrix);
}

TextRenderer::~TextRenderer(){
    delete family;
}
