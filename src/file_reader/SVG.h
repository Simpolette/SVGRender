#ifndef _SVG_H_
#define _SVG_H_

#include <iostream>
#include <string>
#include <cstring>
#include <windows.h>
#include <Gdiplus.h>
#include <sstream>
#include <algorithm>

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
    bool checkNumber(char ch);
    void standardizeString(std::string& s);
    int countAttrVal(const std::string& attrValue);
    Stroke parseStroke(rapidxml::xml_attribute<> *attr);
    Fill parseFill(rapidxml::xml_attribute<> *attr);
    Transform parseTransform(const std::string& transformVal);
    RawElement* parseRect(rapidxml::xml_node<> *node);
    RawElement* parseCircle(rapidxml::xml_node<> *node);
    RawElement* parseEllipse(rapidxml::xml_node<> *node);
    RawElement* parsePolygon(rapidxml::xml_node<> *node);
    RawElement* parsePolyline(rapidxml::xml_node<> *node);
    RawElement* parseLine(rapidxml::xml_node<> *node);
    RawElement* parseText(rapidxml::xml_node<> *node);
    RawElement* parseGroup(rapidxml::xml_node<> * node, rapidxml::xml_document<>& doc);
    RawElement* parsePath(rapidxml::xml_node<> *node);
    std::vector<std::pair<char, Gdiplus::Point>> parsePathData(rapidxml::xml_attribute<> *attr);

public:
    std::vector<RawElement*> parseSVGFile(const std::string& filePath);
};

#endif