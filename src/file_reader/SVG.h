#ifndef _SVG_H_
#define _SVG_H_

#include <iostream>
#include <string>
#include <cstring>
#include <windows.h>
#include <Gdiplus.h>
#include <sstream>

#include "RawElement.h"
#include "Circle.h"
#include "Ellipse.h"
#include "Line.h"
#include "Polygon.h"
#include "Polyline.h"
#include "Rect.h"
#include "Text.h"
#include "Group.h"
#include "Path.h"
#include "xml/rapidxml.hpp"
#include "xml/rapidxml_utils.hpp"

class GetSVG {
private:
    bool checkAlpha(char ch);
    RawElement* parseRect(rapidxml::xml_node<> *node);
    RawElement* parseCircle(rapidxml::xml_node<> *node);
    RawElement* parseEllipse(rapidxml::xml_node<> *node);
    RawElement* parsePolygon(rapidxml::xml_node<> *node);
    RawElement* parsePolyline(rapidxml::xml_node<> *node);
    RawElement* parseLine(rapidxml::xml_node<> *node);
    RawElement* parseText(rapidxml::xml_node<> *node);
    RawElement* parseGroup(rapidxml::xml_node<> * node);
    void parsePathData(const std::string& d, std::vector<std::pair<char, Gdiplus::Point>>& pathData);
    RawElement* parsePath(rapidxml::xml_node<> *node);
    void processTransform(const std::string& transformValue, Gdiplus::Point &translate, Gdiplus::Point &scale, double rotate);

    void setData(const std::string& attrName, const std::string& attrValue, std::string& stroke, int& stroke_width, double& stroke_opacity, std::string& stroke_linecap, std::vector<double>& stroke_dasharray, std::string& stroke_linejoin, std::string& fill, double& fill_opacity, std::string& fill_rule);
public:
    void parseSVGFile(std::vector<RawElement*>& vec, const std::string& filePath);
};

#endif