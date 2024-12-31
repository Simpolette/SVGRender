#include "TextRenderer.h"

TextRenderer::TextRenderer(const Fill& fill, const Stroke& stroke, const Transform& transform, RawElement* rawElement) 
: Renderer(fill, stroke, transform) {
    Text* text = dynamic_cast<Text*>(rawElement);
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

    std::wstring content = converter.from_bytes(text->getContent());
    int length = content.size();
    Gdiplus::FontFamily* family;
    int style = 0;
    Gdiplus::REAL emSize = (float)text->getFontSize();
    Gdiplus::PointF origin;
    Gdiplus::StringFormat format;

    family = new Gdiplus::FontFamily(converter.from_bytes(text->getFontFamily()).c_str());
    if (family->GetLastStatus() != Gdiplus::Ok){
        delete family;
        family = new Gdiplus::FontFamily(L"Times New Roman");
    }

    double ascent = family->GetCellAscent(0);
    double emHeight = family->GetEmHeight(0);
    Gdiplus::PointF point = text->getPoint();
    double ascentOffset = emSize * (static_cast<Gdiplus::REAL>(ascent) / emHeight);
    double topLeftY = point.Y - ascentOffset;

    origin = Gdiplus::PointF(point.X, topLeftY);

    Gdiplus::Bitmap bitmap(1, 1);
    Gdiplus::Graphics graphics(&bitmap);
    Gdiplus::RectF textBounds;
    Gdiplus::Font font(family, emSize, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
    graphics.MeasureString(content.c_str(), -1, &font, origin, &textBounds);
    if (text->getTextAnchor() == "middle"){
        format.SetAlignment(Gdiplus::StringAlignmentCenter);
    }
    else if (text->getTextAnchor() == "end"){
        origin.X += 0.15 * emSize;
        format.SetAlignment(Gdiplus::StringAlignmentFar);
    }
    else{
        origin.X -= 0.15 * emSize;
        format.SetAlignment(Gdiplus::StringAlignmentNear);
    }

    double fontStyle;
    if (text->getFontStyle() == "italic"){
        fontStyle = 2;
    }
    else{
        fontStyle = 0;
    }

    double fontWeight;
    if (text->getFontWeight() == "bold"){
        fontWeight = 1;
    }
    else{
        fontWeight = 0;
    }
    style = fontStyle + fontWeight;

    textGraphics.StartFigure();
    textGraphics.AddString(content.c_str(), length, family, style, emSize, origin, &format);
    delete family;

    Gdiplus::RectF bound;
    textGraphics.GetBounds(&bound);

    if (!brush){
        brush = fill.getGradientBrush(bound);
    }
}

void TextRenderer::render(Gdiplus::Graphics& graphics) const{
    Gdiplus::Matrix originalMatrix;
    graphics.GetTransform(&originalMatrix);
    graphics.MultiplyTransform(matrix);

    graphics.FillPath(brush, &textGraphics);
    graphics.DrawPath(pen, &textGraphics);

    graphics.SetTransform(&originalMatrix);
}