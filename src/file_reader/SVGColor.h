#ifndef _SVG_COLOR_H_
#define _SVG_COLOR_H_

#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <windows.h>
#include <Gdiplus.h>

static std::unordered_map<std::string, Gdiplus::Color> mpColorName = {
    {"White", Gdiplus::Color(255,255,255)},
    {"Black", Gdiplus::Color(0,0,0)},
    {"Red", Gdiplus::Color(255,0,0)},
    {"Green", Gdiplus::Color(0,255,0)},
    {"Blue", Gdiplus::Color(0,0,255)},
    {"Yellow", Gdiplus::Color(255,255,0)},
    {"Orange", Gdiplus::Color(255,165,0)},
    {"Pink", Gdiplus::Color(255,192,203)},
    {"Purple", Gdiplus::Color(128,0,128)},
    {"Cyan", Gdiplus::Color(0,255,255)},
    {"Magenta", Gdiplus::Color(255,0,255)},
    {"Gray", Gdiplus::Color(128,128,128)},
    {"Brown", Gdiplus::Color(165,42,42)},
    {"Teal", Gdiplus::Color(0,128,128)},
    {"Navy", Gdiplus::Color(0,0,128)},
    {"Gold", Gdiplus::Color(255,215,0)},
    {"Silver", Gdiplus::Color(192,192,192)},
    {"Lime", Gdiplus::Color(0,255,0)},
    {"Lavender", Gdiplus::Color(230,230,250)},
    {"Peach", Gdiplus::Color(255,218,185)},
    {"Maroon", Gdiplus::Color(128,0,0)},
    {"Olive", Gdiplus::Color(128,128,0)},
    {"Coral", Gdiplus::Color(255,127,80)},
    {"Turquoise", Gdiplus::Color(64,224,208)},
    {"Mint", Gdiplus::Color(152,255,152)},
    {"Salmon", Gdiplus::Color(250,128,114)},
    {"Plum", Gdiplus::Color(221,160,221)},
    {"Indigo", Gdiplus::Color(75,0,130)},
    {"Crimson", Gdiplus::Color(220,20,60)},
    {"Amber", Gdiplus::Color(255,191,0)},
    {"Chartreuse", Gdiplus::Color(127,255,0)},
    {"Periwinkle", Gdiplus::Color((204,204,255))},
    {"Khaki", Gdiplus::Color(240,230,140)},
    {"Aquamarine", Gdiplus::Color(127,255,212)},
    {"Chocolate", Gdiplus::Color(210,105,30)},
    {"Slate Gray", Gdiplus::Color(112,128,144)},
    {"Seashell", Gdiplus::Color(255,245,238)},
    {"Honeydew", Gdiplus::Color(240,255,240)},
    {"Orchid", Gdiplus::Color(218,112,214)}
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
};

#endif