#include "TextRenderer.h"

TextRenderer::TextRenderer(const Fill& fill, const Stroke& stroke, const Transform& transform, const Text& text) 
: Renderer(fill, stroke, transform) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    Gdiplus::FontFamily family(L"Arial");
    int ascent = family.GetCellAscent(0);
    int emHeight = family.GetEmHeight(0);
    Gdiplus::Point point = text.getPoint();

    content = converter.from_bytes(text.getContent());
    length = content.size();
    style = 0;
    emSize = (float)text.getFontSize();
    int ascentOffset = floor(emSize * (static_cast<Gdiplus::REAL>(ascent) / emHeight));
    int topLeftY = point.Y - ascentOffset;

    origin = Gdiplus::Point(point.X, topLeftY);
    format.SetAlignment(Gdiplus::StringAlignmentNear);
}

void TextRenderer::render(Gdiplus::Graphics& graphics) const{
    Gdiplus::GraphicsPath text;
    text.StartFigure();
    Gdiplus::FontFamily family(L"Arial");
    text.AddString(content.c_str(), length, &family, style, emSize, origin, &format);

    graphics.FillPath(brush, &text);
    graphics.DrawPath(pen, &text);
}
