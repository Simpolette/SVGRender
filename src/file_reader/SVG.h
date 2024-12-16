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

private:
    bool checkAlpha(char ch);
    bool checkNumber(char ch);
    void standardizeString(std::string& s);
    int countAttrVal(const std::string& attrValue);
    Stroke parseStroke(rapidxml::xml_attribute<> *attr);
    Fill parseFill(rapidxml::xml_attribute<> *attr, std::vector<Gradient*> gradients);
    Transform parseTransform(const std::string& transformVal);
    RawElement* parseRect(rapidxml::xml_node<> *node, std::vector<Gradient*> gradients);
    RawElement* parseCircle(rapidxml::xml_node<> *node, std::vector<Gradient*> gradients);
    RawElement* parseEllipse(rapidxml::xml_node<> *node, std::vector<Gradient*> gradients);
    RawElement* parsePolygon(rapidxml::xml_node<> *node, std::vector<Gradient*> gradients);
    RawElement* parsePolyline(rapidxml::xml_node<> *node, std::vector<Gradient*> gradients);
    RawElement* parseLine(rapidxml::xml_node<> *node, std::vector<Gradient*> gradients);
    RawElement* parseText(rapidxml::xml_node<> *node, std::vector<Gradient*> gradients);
    RawElement* parseGroup(rapidxml::xml_node<> * node, rapidxml::xml_document<>& doc, std::vector<Gradient*> gradients);
    RawElement* parsePath(rapidxml::xml_node<> *node, std::vector<Gradient*> gradients);
    double getDoubleValue(const std::string &s);
    void gradientAttribute(const std::string attName, const std::string attValue, double &x1, double &y1, double &x2, double y2, double &cx, double &cy, double &r, double &fx, double &fy, double &fr);
    void stopAttribute(const std::string attName, const std::string attValue, double &offset, std::string &color, double &opacity);
    std::vector<Gradient*> parseGradient(rapidxml::xml_node<> *node); 
    std::vector<std::pair<char, Gdiplus::PointF>> parsePathData(rapidxml::xml_attribute<> *attr);

public:
    std::vector<RawElement*> parseSVGFile(const std::string& filePath);
    double getViewWidth() const;
    double getViewHeight() const;
    Gdiplus::PointF getBoxOrigin() const;
    double getBoxWidth() const;
    double getBoxHeight() const;
};

#endif