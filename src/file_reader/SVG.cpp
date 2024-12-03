#include "SVG.h"

void GetSVG::processTransform(const std::string& transformValue, Gdiplus::Point &translate, Gdiplus::Point &scale, double rotate) {
    std::istringstream ss(transformValue);
    std::string transform;

    while (getline(ss, transform, ')')) {
        std::istringstream ss2(transform);
        std::string temp;
        getline(ss2, temp, '(');
        if (temp == "translate") {
            std::string tempValue;
            int x = 0, y = 0;
            getline(ss2, tempValue, ',');
            x = stoi(tempValue);
            getline(ss2, tempValue);
            y = stoi(tempValue);

            translate = Gdiplus::Point(x, y);
        }
        else if (temp == "scale") {
            std::string tempValue;
            int x = 0, y = 0;
            getline(ss2, tempValue, ',');
            x = stoi(tempValue);
            getline(ss2, tempValue);
            y = stoi(tempValue);

            scale = Gdiplus::Point(x, y);
        }
        else if (temp == "rotate") {
            std::string tempValue;
            getline(ss2, tempValue);
            rotate = stod(tempValue);
        }
    }
}

void GetSVG::setData(const std::string& attrName, const std::string& attrValue, std::string& stroke, int& stroke_width, double& stroke_opacity, std::string& stroke_linecap, std::vector<double>& stroke_dasharray, std::string& stroke_linejoin, std::string& fill, double& fill_opacity, std::string& fill_rule){
    if (attrName == "stroke") {
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

RawElement* GetSVG::parseRect(rapidxml::xml_node<> *node){
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

    Gdiplus::Point translate;
    Gdiplus::Point scale;
    double rotate = 0;

    for (rapidxml::xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
        std::string attrName = attr->name();
        std::string attrValue = attr->value();

        if (attrName == "transform") {
            this->processTransform(attrValue, translate, scale, rotate);
        }

        this->setData(attrName, attrValue, stroke, stroke_width, stroke_opacity, stroke_linecap, stroke_dasharray, stroke_linejoin, fill, fill_opacity, fill_rule);

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
    Transform transformTemp(translate, scale, rotate);

    return new Rectan(Gdiplus::Point(x, y), width, height, strokeTemp, fillTemp, transformTemp);
}

RawElement* GetSVG::parseCircle(rapidxml::xml_node<> *node){
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

    Gdiplus::Point translate;
    Gdiplus::Point scale;
    double rotate = 0;

    for (rapidxml::xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
        std::string attrName = attr->name();
        std::string attrValue = attr->value();

        if (attrName == "transform") {
            this->processTransform(attrValue, translate, scale, rotate);
        }

        this->setData(attrName, attrValue, stroke, stroke_width, stroke_opacity, stroke_linecap, stroke_dasharray, stroke_linejoin, fill, fill_opacity, fill_rule);

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
    Transform transformTemp(translate, scale, rotate);

    return new Circle(Gdiplus::Point(x, y), radius, strokeTemp, fillTemp, transformTemp);
}

RawElement* GetSVG::parseEllipse(rapidxml::xml_node<> *node){
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

    Gdiplus::Point translate;
    Gdiplus::Point scale;
    double rotate = 0;

    for (rapidxml::xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
        std::string attrName = attr->name();
        std::string attrValue = attr->value();

        if (attrName == "transform") {
            this->processTransform(attrValue, translate, scale, rotate);
        }

        this->setData(attrName, attrValue, stroke, stroke_width, stroke_opacity, stroke_linecap, stroke_dasharray, stroke_linejoin, fill, fill_opacity, fill_rule);

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
    Transform transformTemp(translate, scale, rotate);

    return new Ellip(Gdiplus::Point(x, y), rx, ry, strokeTemp, fillTemp, transformTemp);
}

RawElement* GetSVG::parsePolygon(rapidxml::xml_node<> *node){
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

    Gdiplus::Point translate;
    Gdiplus::Point scale;
    double rotate = 0;

    for (rapidxml::xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
        std::string attrName = attr->name();
        std::string attrValue = attr->value();

        if (attrName == "transform") {
            this->processTransform(attrValue, translate, scale, rotate);
        }

        this->setData(attrName, attrValue, stroke, stroke_width, stroke_opacity, stroke_linecap, stroke_dasharray, stroke_linejoin, fill, fill_opacity, fill_rule);

        if (attrName == "points"){
            points = attrValue;
        }
    }
    Stroke strokeTemp(stroke, stroke_width, stroke_opacity, stroke_linecap, stroke_dasharray, stroke_linejoin);
    Fill fillTemp(fill, fill_opacity, fill_rule);
    Transform transformTemp(translate, scale, rotate);

    return new PolyGon(points, strokeTemp, fillTemp, transformTemp);
}

RawElement* GetSVG::parsePolyline(rapidxml::xml_node<> *node){
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

    Gdiplus::Point translate;
    Gdiplus::Point scale;
    double rotate = 0;

    for (rapidxml::xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
        std::string attrName = attr->name();
        std::string attrValue = attr->value();

        if (attrName == "transform") {
            this->processTransform(attrValue, translate, scale, rotate);
        }

        this->setData(attrName, attrValue, stroke, stroke_width, stroke_opacity, stroke_linecap, stroke_dasharray, stroke_linejoin, fill, fill_opacity, fill_rule);

        if (attrName == "points"){
            points = attrValue;
        }
    }
    Stroke strokeTemp(stroke, stroke_width, stroke_opacity, stroke_linecap, stroke_dasharray, stroke_linejoin);
    Fill fillTemp(fill, fill_opacity, fill_rule);
    Transform transformTemp(translate, scale, rotate);

    return new PolyLine(points, strokeTemp, fillTemp, transformTemp);
}

RawElement* GetSVG::parseLine(rapidxml::xml_node<> *node){
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

    Gdiplus::Point translate;
    Gdiplus::Point scale;
    double rotate = 0;

    for (rapidxml::xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
        std::string attrName = attr->name();
        std::string attrValue = attr->value();

        if (attrName == "transform") {
            this->processTransform(attrValue, translate, scale, rotate);
        }

        this->setData(attrName, attrValue, stroke, stroke_width, stroke_opacity, stroke_linecap, stroke_dasharray, stroke_linejoin, fill, fill_opacity, fill_rule);

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
    Transform transformTemp(translate, scale, rotate);

    return new Line(Gdiplus::Point(x1, y1), Gdiplus::Point(x2, y2), strokeTemp, fillTemp, transformTemp);
}

RawElement* GetSVG::parseText(rapidxml::xml_node<> *node){
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

    Gdiplus::Point translate;
    Gdiplus::Point scale;
    double rotate = 0;

    for (rapidxml::xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
        std::string attrName = attr->name();
        std::string attrValue = attr->value();

        if (attrName == "transform") {
            this->processTransform(attrValue, translate, scale, rotate);
        }

        this->setData(attrName, attrValue, stroke, stroke_width, stroke_opacity, stroke_linecap, stroke_dasharray, stroke_linejoin, fill, fill_opacity, fill_rule);

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
    Transform transformTemp(translate, scale, rotate);

    return new Text(content, Gdiplus::Point(x, y), font_size, strokeTemp, fillTemp, transformTemp);
}

RawElement* GetSVG::parseGroup(rapidxml::xml_node<> *node) {
    std::string stroke = "";
    int stroke_width = 1;
    double stroke_opacity = 0;
    std::string stroke_linecap = "butt";
    std::vector<double> stroke_dasharray;
    std::string stroke_linejoin = "miter";

    std::string fill = "";
    double fill_opacity = 1;
    std::string fill_rule = "nonezero";

    Gdiplus::Point translate;
    Gdiplus::Point scale;
    double rotate = 0;

    std::vector<RawElement*> vec;

    for (rapidxml::xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
        std::string attrName = attr->name();
        std::string attrValue = attr->value();

        if (attrName == "transform") {
            this->processTransform(attrValue, translate, scale, rotate);
        }
        else {
            this->setData(attrName, attrValue, stroke, stroke_width, stroke_opacity, stroke_linecap, stroke_dasharray, stroke_linejoin, fill, fill_opacity, fill_rule);
        }
    }

    for (rapidxml::xml_node<>* child = node->first_node(); child; child = child->next_sibling()) {
        std::string ShapeName = child->name();
        if (ShapeName == "rect"){
            RawElement* rect = this->parseRect(child);
            vec.push_back(rect);
        }
        else if (ShapeName == "circle"){
            RawElement* circle = this->parseCircle(child);
            vec.push_back(circle);
        }
        else if (ShapeName == "ellipse"){
            RawElement* ellip = this->parseEllipse(child);
            vec.push_back(ellip);
        }
        else if (ShapeName == "polygon"){
            RawElement* polygon = this->parsePolygon(child);
            vec.push_back(polygon);
        }
        else if (ShapeName == "polyline"){
            RawElement* polyline = this->parsePolyline(child);
            vec.push_back(polyline);
        }
        else if (ShapeName == "line"){
            RawElement* line = this->parseLine(child);
            vec.push_back(line);
        }
        else if (ShapeName == "g") {
            RawElement* group = this->parseGroup(child);
            vec.push_back(group);
        }
        else if (ShapeName == "path") {
            RawElement* path = this->parsePath(child);
            vec.push_back(path);
        }
        else if (child->value()) {
            RawElement* text = this->parseText(child);
            vec.push_back(text);
        }
    }
    
    Stroke strokeTemp(stroke, stroke_width, stroke_opacity, stroke_linecap, stroke_dasharray, stroke_linejoin);
    Fill fillTemp(fill, fill_opacity, fill_rule);
    Transform transformTemp(translate, scale, rotate);

    return new Group(vec, strokeTemp, fillTemp, transformTemp);
}

bool GetSVG::checkAlpha(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'); 
}

void GetSVG::parsePathData(const std::string& Data, std::vector<std::pair<char, Gdiplus::Point>>& pathData) {
    std::string d = Data + 'E';
    int n = d.size();
    int i = 0;
    while (i < n) {
        char ch = d[i];
        if (ch == 'M' || ch == 'm' || ch == 'L' || ch == 'l') {
            bool check = true;
            std::string x, y;
            i++;
            while (!this->checkAlpha(d[i])) {
                if (d[i] == ',') {
                    check = false;
                }
                else if (check) {
                    x += d[i];
                }
                else {
                    y += d[i];
                }
                i++;
            }
            pathData.push_back(std::pair(ch, Gdiplus::Point(stoi(x), stoi(y))));
            i--;
        }
        else if (ch == 'C' || ch == 'c') {
            i++;
            int j = i;
            while (this->checkAlpha(j)) {
                j++;
            }
            int len = j - i;
            std::string temp = d.substr(i, len);

            std::stringstream ss(temp);

            int x1, y1, x2, y2, x3, y3;
            ss >> x1;
            ss.ignore();
            ss >> y1;
            ss.ignore();
            ss >> x2;
            ss.ignore();
            ss >> y2;
            ss.ignore();
            ss >> x3;
            ss.ignore();
            ss >> y3;

            pathData.push_back(std::pair(ch, Gdiplus::Point(x1, y1)));
            pathData.push_back(std::pair(ch, Gdiplus::Point(x2, y2)));
            pathData.push_back(std::pair(ch, Gdiplus::Point(x3, y3)));
        }
        else if (ch == 'H' || ch == 'h' || ch == 'V' || ch == 'v') {
            i++;
            std::string temp;
            while (!this->checkAlpha(d[i])) {
                temp += d[i];
                i++;
            }
            if (ch == 'H' || ch == 'h') {
                pathData.push_back(std::pair(ch, Gdiplus::Point(stoi(temp), 0)));
            }
            else {
                pathData.push_back(std::pair(ch, Gdiplus::Point(0, stoi(temp))));
            }
            i--;
        }
        else if (ch == 'Z' || ch == 'z') {
            pathData.push_back(std::pair(ch, Gdiplus::Point(0, 0)));
        }
        i++;
    }
}

RawElement* GetSVG::parsePath(rapidxml::xml_node<> *node) {
    std::string stroke = "";
    int stroke_width = 1;
    double stroke_opacity = 0;
    std::string stroke_linecap = "butt";
    std::vector<double> stroke_dasharray;
    std::string stroke_linejoin = "miter";

    std::string fill = "";
    double fill_opacity = 1;
    std::string fill_rule = "nonezero";

    Gdiplus::Point translate;
    Gdiplus::Point scale;
    double rotate = 0;

    for (rapidxml::xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
        std::string attrName = attr->name();
        std::string attrValue = attr->value();

        if (attrName == "transform") {
            this->processTransform(attrValue, translate, scale, rotate);
        }

        this->setData(attrName, attrValue, stroke, stroke_width, stroke_opacity, stroke_linecap, stroke_dasharray, stroke_linejoin, fill, fill_opacity, fill_rule);
    }

    rapidxml::xml_attribute<> *d_attr = node->first_attribute("d");
    std::vector<std::pair<char, Gdiplus::Point>> pathData;
    if (d_attr) {
        std::string d = node->first_attribute("d")->value();
        parsePathData(d, pathData);
    }

    Stroke strokeTemp(stroke, stroke_width, stroke_opacity, stroke_linecap, stroke_dasharray, stroke_linejoin);
    Fill fillTemp(fill, fill_opacity, fill_rule);
    Transform transformTemp(translate, scale, rotate);

    return new Path(pathData, strokeTemp, fillTemp, transformTemp);
}

void GetSVG::parseSVGFile(std::vector<RawElement*>& vec, const std::string& filePath){
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
                RawElement* rect = this->parseRect(child);
                vec.push_back(rect);
            }
            else if (ShapeName == "circle"){
                RawElement* circle = this->parseCircle(child);
                vec.push_back(circle);
            }
            else if (ShapeName == "ellipse"){
                RawElement* ellip = this->parseEllipse(child);
                vec.push_back(ellip);
            }
            else if (ShapeName == "polygon"){
                RawElement* polygon = this->parsePolygon(child);
                vec.push_back(polygon);
            }
            else if (ShapeName == "polyline"){
                RawElement* polyline = this->parsePolyline(child);
                vec.push_back(polyline);
            }
            else if (ShapeName == "line"){
                RawElement* line = this->parseLine(child);
                vec.push_back(line);
            }
            else if (ShapeName == "g") {
                RawElement* group = this->parseGroup(child);
                vec.push_back(group);
            }
            else if (ShapeName == "path") {
                RawElement* path = this->parsePath(child);
                vec.push_back(path);
            }
            else if (child->value()) {
                RawElement* text = this->parseText(child);
                vec.push_back(text);
            }
        }
    }

    delete[] xml;
}