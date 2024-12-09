#ifndef _SVG_COLOR_H_
#define _SVG_COLOR_H_

#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <windows.h>
#include <Gdiplus.h>

static std::unordered_map<std::string, Gdiplus::Color> mpColorName = {
    {"white", Gdiplus::Color(255,255,255)},
    {"black", Gdiplus::Color(0,0,0)},
    {"red", Gdiplus::Color(255,0,0)},
    {"green", Gdiplus::Color(0,255,0)},
    {"blue", Gdiplus::Color(0,0,255)},
    {"yellow", Gdiplus::Color(255,255,0)},
    {"orange", Gdiplus::Color(255,165,0)},
    {"pink", Gdiplus::Color(255,192,203)},
    {"purple", Gdiplus::Color(128,0,128)},
    {"cyan", Gdiplus::Color(0,255,255)},
    {"magenta", Gdiplus::Color(255,0,255)},
    {"gray", Gdiplus::Color(128,128,128)},
    {"brown", Gdiplus::Color(165,42,42)},
    {"teal", Gdiplus::Color(0,128,128)},
    {"navy", Gdiplus::Color(0,0,128)},
    {"gold", Gdiplus::Color(255,215,0)},
    {"silver", Gdiplus::Color(192,192,192)},
    {"lime", Gdiplus::Color(0,255,0)},
    {"lavender", Gdiplus::Color(230,230,250)},
    {"peach", Gdiplus::Color(255,218,185)},
    {"maroon", Gdiplus::Color(128,0,0)},
    {"olive", Gdiplus::Color(128,128,0)},
    {"coral", Gdiplus::Color(255,127,80)},
    {"turquoise", Gdiplus::Color(64,224,208)},
    {"mint", Gdiplus::Color(152,255,152)},
    {"salmon", Gdiplus::Color(250,128,114)},
    {"plum", Gdiplus::Color(221,160,221)},
    {"indigo", Gdiplus::Color(75,0,130)},
    {"crimson", Gdiplus::Color(220,20,60)},
    {"amber", Gdiplus::Color(255,191,0)},
    {"chartreuse", Gdiplus::Color(127,255,0)},
    {"periwinkle", Gdiplus::Color((204,204,255))},
    {"khaki", Gdiplus::Color(240,230,140)},
    {"aquamarine", Gdiplus::Color(127,255,212)},
    {"chocolate", Gdiplus::Color(210,105,30)},
    {"slate gray", Gdiplus::Color(112,128,144)},
    {"seashell", Gdiplus::Color(255,245,238)},
    {"honeydew", Gdiplus::Color(240,255,240)},
    {"orchid", Gdiplus::Color(218,112,214)}
};

class SVGColor{

private:
    int r;
    int g;
    int b;
public:
    SVGColor(const std::string& color);
    int getR() const;
    int getG() const;
    int getB() const;
    int getValue(const std::string& s) const;
    std::string getLower(const std::string &color) const;
};

#endif