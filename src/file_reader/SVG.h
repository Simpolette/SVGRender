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
    double viewWidth;
    double viewHeight;
    Gdiplus::PointF boxOrigin;
    double boxWidth;
    double boxHeight;
    std::unordered_map<std::string, Gradient*> gradients;

private:
    bool checkCommand(char ch);
    bool checkNumber(char ch);
    void standardizeString(std::string& s);
    std::string standardizeText(std::string text);
    int countAttrVal(const std::string& attrValue);
    Stroke parseStroke(rapidxml::xml_attribute<> *attr);
    Fill parseFill(rapidxml::xml_attribute<> *attr);
    void parseStyle(const std::string &style, Stroke& stroke, Fill& fill);
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
    double getDoubleValue(const std::string &s);
    void parseGradient(rapidxml::xml_node<> *node); 
    std::vector<std::pair<char, Gdiplus::PointF>> parsePathData(rapidxml::xml_attribute<> *attr);

public:
    ~GetSVG();
    std::vector<RawElement*> parseSVGFile(const std::string& filePath);
    double getViewWidth() const;
    double getViewHeight() const;
    Gdiplus::PointF getBoxOrigin() const;
    double getBoxWidth() const;
    double getBoxHeight() const;
};

#endif