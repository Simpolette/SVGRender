#include "SVG.h"

void setData(const std::string& attrName, const std::string& attrValue, std::string& stroke, int& stroke_width, double& stroke_opacity, std::string& stroke_linecap, std::vector<double>& stroke_dasharray, std::string& stroke_linejoin, std::string& fill, double& fill_opacity, std::string& fill_rule){
    if (attrName == "stroke"){
        stroke = attrValue;
    }
    else if (attrName == "stroke-width"){
        stroke_width = stoi(attrValue);
    }
    else if (attrName == "stroke-opacity"){
        stroke_opacity = stod(attrValue);
    }
    else if (attrName == "stroke-linecap"){
        stroke_linecap = attrValue;
    }
    else if (attrName == "stroke-dasharray"){
        //Stroke_dasharray
    }
    else if (attrName == "stroke-linejoin"){
        stroke_linejoin = attrValue;
    }
    else if (attrName == "fill"){
        fill = attrValue;
    }
    else if (attrName == "fill-opacity"){
        fill_opacity = stod(attrValue);
    }
    else if (attrName == "fill-rule"){
        fill_rule = attrValue;
    }
}

RawElement* parseRect(rapidxml::xml_node<> *node){
    std::string stroke = "";
    int stroke_width = 1;
    double stroke_opacity = 1;
    std::string stroke_linecap = "butt";
    std::vector<double> stroke_dasharray;
    std::string stroke_linejoin = "miter";

    std::string fill = "";
    double fill_opacity = 1;
    std::string fill_rule = "nonezero";

    int x = 0, y = 0, width = 0, height = 0;

    for (rapidxml::xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
        std::string attrName = attr->name();
        std::string attrValue = attr->value();
        setData(attrName, attrValue, stroke, stroke_width, stroke_opacity, stroke_linecap, stroke_dasharray, stroke_linejoin, fill, fill_opacity, fill_rule);

        if (attrName == "x"){
            x = stoi(attrValue);
        }
        else if (attrName == "y"){
            y = stoi(attrValue);
        }
        else if (attrName == "width"){
            width = stoi(attrValue);
        }
        else if (attrName == "height"){
            height = stoi(attrValue);
        }
    }
    Stroke strokeTemp(stroke, stroke_width, stroke_opacity, stroke_linecap, stroke_dasharray, stroke_linejoin);
    Fill fillTemp(fill, fill_opacity, fill_rule);
    return new Rectan(Gdiplus::Point(x, y), width, height, strokeTemp, fillTemp);
}

RawElement* parseCircle(rapidxml::xml_node<> *node){
    std::string stroke = "";
    int stroke_width = 1;
    double stroke_opacity = 1;
    std::string stroke_linecap = "butt";
    std::vector<double> stroke_dasharray;
    std::string stroke_linejoin = "miter";

    std::string fill = "";
    double fill_opacity = 1;
    std::string fill_rule = "nonezero";

    int x = 0, y = 0, radius = 0;

    for (rapidxml::xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
        std::string attrName = attr->name();
        std::string attrValue = attr->value();
        setData(attrName, attrValue, stroke, stroke_width, stroke_opacity, stroke_linecap, stroke_dasharray, stroke_linejoin, fill, fill_opacity, fill_rule);

        if (attrName == "cx"){
            x = stoi(attrValue);
        }
        else if (attrName == "cy"){
            y = stoi(attrValue);
        }
        else if (attrName == "r"){
            radius = stoi(attrValue);
        }
    }
    Stroke strokeTemp(stroke, stroke_width, stroke_opacity, stroke_linecap, stroke_dasharray, stroke_linejoin);
    Fill fillTemp(fill, fill_opacity, fill_rule);
    return new Circle(Gdiplus::Point(x, y), radius, strokeTemp, fillTemp);
}

RawElement* parseEllipse(rapidxml::xml_node<> *node){
    std::string stroke = "";
    int stroke_width = 1;
    double stroke_opacity = 1;
    std::string stroke_linecap = "butt";
    std::vector<double> stroke_dasharray;
    std::string stroke_linejoin = "miter";

    std::string fill = "";
    double fill_opacity = 1;
    std::string fill_rule = "nonezero";

    int x = 0, y = 0, rx = 0, ry = 0;

    for (rapidxml::xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
        std::string attrName = attr->name();
        std::string attrValue = attr->value();
        setData(attrName, attrValue, stroke, stroke_width, stroke_opacity, stroke_linecap, stroke_dasharray, stroke_linejoin, fill, fill_opacity, fill_rule);

        if (attrName == "cx"){
            x = stoi(attrValue);
        }
        else if (attrName == "cy"){
            y = stoi(attrValue);
        }
        else if (attrName == "rx"){
            rx = stoi(attrValue);
        }
        else if (attrName == "ry"){
            ry = stoi(attrValue);
        }
    }
    Stroke strokeTemp(stroke, stroke_width, stroke_opacity, stroke_linecap, stroke_dasharray, stroke_linejoin);
    Fill fillTemp(fill, fill_opacity, fill_rule);
    return new Ellip(Gdiplus::Point(x, y), rx, ry, strokeTemp, fillTemp);
}

RawElement* parsePolygon(rapidxml::xml_node<> *node){
    std::string stroke = "";
    int stroke_width = 1;
    double stroke_opacity = 1;
    std::string stroke_linecap = "butt";
    std::vector<double> stroke_dasharray;
    std::string stroke_linejoin = "miter";

    std::string fill = "";
    double fill_opacity = 1;
    std::string fill_rule = "nonezero";

    std::string points = "";

    for (rapidxml::xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
        std::string attrName = attr->name();
        std::string attrValue = attr->value();
        setData(attrName, attrValue, stroke, stroke_width, stroke_opacity, stroke_linecap, stroke_dasharray, stroke_linejoin, fill, fill_opacity, fill_rule);

        if (attrName == "points"){
            points = attrValue;
        }
    }
    Stroke strokeTemp(stroke, stroke_width, stroke_opacity, stroke_linecap, stroke_dasharray, stroke_linejoin);
    Fill fillTemp(fill, fill_opacity, fill_rule);
    return new PolyGon(points, strokeTemp, fillTemp);
}

RawElement* parsePolyline(rapidxml::xml_node<> *node){
    std::string stroke = "";
    int stroke_width = 1;
    double stroke_opacity = 1;
    std::string stroke_linecap = "butt";
    std::vector<double> stroke_dasharray;
    std::string stroke_linejoin = "miter";

    std::string fill = "";
    double fill_opacity = 1;
    std::string fill_rule = "nonezero";

    std::string points = "";

    for (rapidxml::xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
        std::string attrName = attr->name();
        std::string attrValue = attr->value();
        setData(attrName, attrValue, stroke, stroke_width, stroke_opacity, stroke_linecap, stroke_dasharray, stroke_linejoin, fill, fill_opacity, fill_rule);

        if (attrName == "points"){
            points = attrValue;
        }
    }
    Stroke strokeTemp(stroke, stroke_width, stroke_opacity, stroke_linecap, stroke_dasharray, stroke_linejoin);
    Fill fillTemp(fill, fill_opacity, fill_rule);
    return new PolyLine(points, strokeTemp, fillTemp);
}

RawElement* parseLine(rapidxml::xml_node<> *node){
    std::string stroke = "";
    int stroke_width = 1;
    double stroke_opacity = 1;
    std::string stroke_linecap = "butt";
    std::vector<double> stroke_dasharray;
    std::string stroke_linejoin = "miter";

    std::string fill = "";
    double fill_opacity = 1;
    std::string fill_rule = "nonezero";

    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;

    for (rapidxml::xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
        std::string attrName = attr->name();
        std::string attrValue = attr->value();
        setData(attrName, attrValue, stroke, stroke_width, stroke_opacity, stroke_linecap, stroke_dasharray, stroke_linejoin, fill, fill_opacity, fill_rule);

        if (attrName == "x1"){
            x1 = stoi(attrValue);
        }
        else if (attrName == "y1"){
            y1 = stoi(attrValue);
        }
        else if (attrName == "x2"){
            x2 = stoi(attrValue);
        }
        else if (attrName == "y2"){
            y2 = stoi(attrValue);
        }
    }
    Stroke strokeTemp(stroke, stroke_width, stroke_opacity, stroke_linecap, stroke_dasharray, stroke_linejoin);
    Fill fillTemp(fill, fill_opacity, fill_rule);
    return new Line(Gdiplus::Point(x1, y1), Gdiplus::Point(x2, y2), strokeTemp, fillTemp);
}

RawElement* parseText(rapidxml::xml_node<> *node){
    std::string stroke = "";
    int stroke_width = 1;
    double stroke_opacity = 0;
    std::string stroke_linecap = "butt";
    std::vector<double> stroke_dasharray;
    std::string stroke_linejoin = "miter";

    std::string fill = "";
    double fill_opacity = 1;
    std::string fill_rule = "nonezero";

    std::string content = node->value();
    int x = 0, y = 0, font_size = 16;

    for (rapidxml::xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
        std::string attrName = attr->name();
        std::string attrValue = attr->value();
        setData(attrName, attrValue, stroke, stroke_width, stroke_opacity, stroke_linecap, stroke_dasharray, stroke_linejoin, fill, fill_opacity, fill_rule);

        if (attrName == "x"){
            x = stoi(attrValue);
        }
        else if (attrName == "y"){
            y = stoi(attrValue);
        }
        else if (attrName == "font-size"){
            font_size = stoi(attrValue);
        }
    }
    Stroke strokeTemp(stroke, stroke_width, stroke_opacity, stroke_linecap, stroke_dasharray, stroke_linejoin);
    Fill fillTemp(fill, fill_opacity, fill_rule);
    return new Text(content, Gdiplus::Point(x, y), font_size, strokeTemp, fillTemp);
}

void parseSVGFile(std::vector<RawElement*>& vec, const std::string& filePath){
    std::ifstream svgFile(filePath);
    if (!svgFile) {
        std::cout << "Error: Could not open SVG file.\n";
        return;
    }

    std::string svgContent((std::istreambuf_iterator<char>(svgFile)), std::istreambuf_iterator<char>());
    
    rapidxml::xml_document<> doc;

    char* xml = new char[svgContent.size() + 1];
    std::strcpy(xml, svgContent.c_str());

    doc.parse<0>(xml);

    rapidxml::xml_node<> *root = doc.first_node("svg");
    if (root){
        for (rapidxml::xml_node<> *child = root->first_node(); child; child = child->next_sibling()) {
            std::string ShapeName = child->name();
            if (ShapeName == "rect"){
                RawElement* rect = parseRect(child);
                vec.push_back(rect);
            }
            else if (ShapeName == "circle"){
                RawElement* circle = parseCircle(child);
                vec.push_back(circle);
            }
            else if (ShapeName == "ellipse"){
                RawElement* ellip = parseEllipse(child);
                vec.push_back(ellip);
            }
            else if (ShapeName == "polygon"){
                RawElement* polygon = parsePolygon(child);
                vec.push_back(polygon);
            }
            else if (ShapeName == "polyline"){
                RawElement* polyline = parsePolyline(child);
                vec.push_back(polyline);
            }
            else if (ShapeName == "line"){
                RawElement* line = parseLine(child);
                vec.push_back(line);
            }
            else if (child->value()) {
                RawElement* text = parseText(child);
                vec.push_back(text);
            }
        }
    }

    delete[] xml;
}