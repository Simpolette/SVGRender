#ifndef _SVG_H_
#define _SVG_H_

#include <iostream>
#include <string>
#include <cstring>
#include <windows.h>
#include <Gdiplus.h>

#include "RawElement.h"
#include "Circle.h"
#include "Ellipse.h"
#include "Line.h"
#include "Polygon.h"
#include "Polyline.h"
#include "Rect.h"
#include "Text.h"
#include "xml/rapidxml.hpp"
#include "xml/rapidxml_utils.hpp"

void setData(const std::string& attrName, const std::string& attrValue, std::string& stroke, int& stroke_width, double& stroke_opacity, std::string& stroke_linecap, std::vector<double>& stroke_dasharray, std::string& stroke_linejoin, std::string& fill, double& fill_opacity, std::string& fill_rule);
void parseSVGFile(std::vector<RawElement*>& vec, const std::string& filePath);


#endif