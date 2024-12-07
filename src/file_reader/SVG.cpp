#include "SVG.h"

Stroke GetSVG::parseStroke(rapidxml::xml_attribute<> *attr){
    std::string color = "";
    int width = 1;
    double opacity = 0;
    std::string linecap = "butt";
    std::vector<double> dasharray;
    std::string linejoin = "miter";
    
    for (;attr ;attr = attr->next_attribute()){
        std::string attrName = attr->name();
        std::string attrValue = attr->value();

        if (attrName == "stroke") {
            color = attrValue;
            if (color.find("none") != std::string::npos){
                opacity = 0;
                color = "";
                break;
            }
        }
        else if (attrName == "stroke-width"){
            width = stoi(attrValue);
        }
        else if (attrName == "stroke-opacity"){
            opacity = stod(attrValue);
        }
        else if (attrName == "stroke-linecap"){
            linecap = attrValue;
        }
        else if (attrName == "stroke-dasharray"){
            //Stroke_dasharray
        }
        else if (attrName == "stroke-linejoin"){
            linejoin = attrValue;
        }
    }

    return Stroke(color, width, opacity, linecap, dasharray, linejoin);
}

Fill GetSVG::parseFill(rapidxml::xml_attribute<> *attr){
    std::string color = "";
    double opacity = 1;
    std::string rule = "nonezero";
    
    for (;attr ;attr = attr->next_attribute()){
        std::string attrName = attr->name();
        std::string attrValue = attr->value();

        if (attrName == "fill"){
            color = attrValue;
            if (color.find("none") != std::string::npos){
                opacity = 0;
                color = "";
                break;
            }
        }
        else if (attrName == "fill-opacity"){
            opacity = stod(attrValue);
        }
        else if (attrName == "fill-rule"){
            rule = attrValue;
        }
    }

    return Fill(color, opacity, rule);
}

bool GetSVG::checkNumber(char ch){
    return (ch >= '0' && ch <= '9') || ch == '-';
}

int GetSVG::countAttrVal(const std::string& attrValue){
    int cnt = 0;
    int n = attrValue.size();
    if (n > 0 && attrValue[0] != ' '){
        cnt = 1;
    }
    for (int i = 0; i < n - 1; i++){
        if (attrValue[i] == ' ' && checkNumber(attrValue[i + 1])){
            cnt++;
        }
    }
    return cnt;
}

Transform GetSVG::parseTransform(const std::string& transformVal){
    Gdiplus::PointF translate;
    Gdiplus::PointF scale(1, 1);
    double rotate = 0;

    std::istringstream ss(transformVal);
    std::string transform;

    while (getline(ss, transform, ')')){
        std::istringstream ss2(transform);
        std::string attrName;
        std::string attrValue;
        
        getline(ss2, attrName, '(');
        getline(ss2, attrValue, ')');
        standardizeString(attrValue);
        std::istringstream ss3(attrValue);
        
        int cnt = countAttrVal(attrValue);

        if (attrName.find("translate") != std::string::npos){
            double x, y;
            ss3 >> x >> y;
            translate = Gdiplus::PointF(x, y);
        }
        else if (attrName.find("scale") != std::string::npos){
            double x, y;
            if (cnt >= 1){
                ss3 >> x;
                y = x;
            }
            if (cnt >= 2){
                ss3 >> y;
            }
            scale = Gdiplus::PointF(x, y);
        }
        else if (attrName.find("rotate") != std::string::npos){
            double x, y;
            if (cnt >= 1){
                ss3 >> rotate;
            }
            if (cnt >= 3){
                ss3 >> x >> y;
            }
        }
    }

    return Transform(translate, scale, rotate);
}

RawElement* GetSVG::parseRect(rapidxml::xml_node<> *node){
    int width = 0, height = 0;
    double x = 0, y = 0;
    Stroke stroke = parseStroke(node->first_attribute());
    Fill fill = parseFill(node->first_attribute());
    Transform transform;

    for (rapidxml::xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
        std::string attrName = attr->name();
        std::string attrValue = attr->value();

        if (attrName == "transform"){
            transform = parseTransform(attrValue);
        }
        else if (attrName == "x"){
            x = stod(attrValue);
        }
        else if (attrName == "y"){
            y = stod(attrValue);
        }
        else if (attrName == "width"){
            width = stoi(attrValue);
        }
        else if (attrName == "height"){
            height = stoi(attrValue);
        }
    }
    return new Rectan(Gdiplus::PointF(x, y), width, height, stroke, fill, transform);
}

RawElement* GetSVG::parseCircle(rapidxml::xml_node<> *node){
    int radius = 0;
    double x = 0, y = 0;
    Stroke stroke = parseStroke(node->first_attribute());
    Fill fill = parseFill(node->first_attribute());
    Transform transform;

    for (rapidxml::xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
        std::string attrName = attr->name();
        std::string attrValue = attr->value();

        if (attrName == "transform") {
            transform = parseTransform(attrValue);
        }
        else if (attrName == "cx"){
            x = stod(attrValue);
        }
        else if (attrName == "cy"){
            y = stod(attrValue);
        }
        else if (attrName == "r"){
            radius = stoi(attrValue);
        }
    }
    return new Circle(Gdiplus::PointF(x, y), radius, stroke, fill, transform);
}

RawElement* GetSVG::parseEllipse(rapidxml::xml_node<> *node){
    int rx = 0, ry = 0;
    double x = 0, y = 0;
    Stroke stroke = parseStroke(node->first_attribute());
    Fill fill = parseFill(node->first_attribute());
    Transform transform;
    
    for (rapidxml::xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
        std::string attrName = attr->name();
        std::string attrValue = attr->value();

        if (attrName == "transform") {
            transform = parseTransform(attrValue);
        }
        else if (attrName == "cx"){
            x = stod(attrValue);
        }
        else if (attrName == "cy"){
            y = stod(attrValue);
        }
        else if (attrName == "rx"){
            rx = stoi(attrValue);
        }
        else if (attrName == "ry"){
            ry = stoi(attrValue);
        }
    }

    return new Ellip(Gdiplus::PointF(x, y), rx, ry, stroke, fill, transform);
}

RawElement* GetSVG::parsePolygon(rapidxml::xml_node<> *node){
    std::string points = "";

    Stroke stroke = parseStroke(node->first_attribute());
    Fill fill = parseFill(node->first_attribute());
    Transform transform;

    for (rapidxml::xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
        std::string attrName = attr->name();
        std::string attrValue = attr->value();

        if (attrName == "transform") {
            transform = parseTransform(attrValue);
        }
        else if (attrName == "points"){
            points = attrValue;
            standardizeString(points);
        }
    }
    
    return new PolyGon(points, stroke, fill, transform);
}

RawElement* GetSVG::parsePolyline(rapidxml::xml_node<> *node){
    std::string points = "";

    Stroke stroke = parseStroke(node->first_attribute());
    Fill fill = parseFill(node->first_attribute());
    Transform transform;

    for (rapidxml::xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
        std::string attrName = attr->name();
        std::string attrValue = attr->value();

        if (attrName == "transform") {
            transform = parseTransform(attrValue);
        }
        else if (attrName == "points"){
            points = attrValue;
            standardizeString(points);
        }
    }

    return new PolyLine(points, stroke, fill, transform);
}

RawElement* GetSVG::parseLine(rapidxml::xml_node<> *node){
    double x1 = 0, y1 = 0, x2 = 0, y2 = 0;

    Stroke stroke = parseStroke(node->first_attribute());
    Fill fill = parseFill(node->first_attribute());
    Transform transform;

    for (rapidxml::xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
        std::string attrName = attr->name();
        std::string attrValue = attr->value();

        if (attrName == "transform") {
            transform = parseTransform(attrValue);
        }
        else if (attrName == "x1"){
            x1 = stod(attrValue);
        }
        else if (attrName == "y1"){
            y1 = stod(attrValue);
        }
        else if (attrName == "x2"){
            x2 = stod(attrValue);
        }
        else if (attrName == "y2"){
            y2 = stod(attrValue);
        }
    }

    return new Line(Gdiplus::PointF(x1, y1), Gdiplus::PointF(x2, y2), stroke, fill, transform);
}

RawElement* GetSVG::parseText(rapidxml::xml_node<> *node){
    std::string content = node->value();
    int font_size = 16;
    double x = 0, y = 0;
    Stroke stroke = parseStroke(node->first_attribute());
    Fill fill = parseFill(node->first_attribute());
    Transform transform;

    for (rapidxml::xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
        std::string attrName = attr->name();
        std::string attrValue = attr->value();

        if (attrName == "transform") {
            transform = parseTransform(attrValue);
        }
        else if (attrName == "x"){
            x = stod(attrValue);
        }
        else if (attrName == "y"){
            y = stod(attrValue);
        }
        else if (attrName == "font-size"){
            font_size = stoi(attrValue);
        }
    }

    return new Text(content, Gdiplus::PointF(x, y), font_size, stroke, fill, transform);
}

RawElement* GetSVG::parseGroup(rapidxml::xml_node<> *node, rapidxml::xml_document<>& doc) {
    Stroke stroke = parseStroke(node->first_attribute());
    Fill fill = parseFill(node->first_attribute());
    Transform transform;

    std::vector<RawElement*> vec;
    std::vector<std::pair<std::string, std::string>> inheritAttr;

    for (rapidxml::xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
        std::string attrName = attr->name();
        std::string attrValue = attr->value();

        if (attrName == "transform") {
            transform = parseTransform(attrValue);
        }
        else{
            inheritAttr.push_back(std::make_pair(attrName, attrValue));
        }
    }

    for (rapidxml::xml_node<>* child = node->first_node(); child; child = child->next_sibling()) {
        std::string shapeName = child->name();
        
        for (int i = 0; i < inheritAttr.size(); i++){
            bool isExisted = false;
            for (rapidxml::xml_attribute<>* attr = child->first_attribute(); attr; attr = attr->next_attribute()){
                if (inheritAttr[i].first == attr->value()){
                    isExisted = true;
                    break;
                }
            }
            if (!isExisted){
                char* attrName = doc.allocate_string(inheritAttr[i].first.c_str());
                char* attrValue = doc.allocate_string(inheritAttr[i].second.c_str());
                rapidxml::xml_attribute<>* attr = doc.allocate_attribute(attrName, attrValue);
                child->append_attribute(attr);
            }
        }

        if (shapeName == "rect"){
            RawElement* rect = this->parseRect(child);
            vec.push_back(rect);
        }
        else if (shapeName == "circle"){
            RawElement* circle = this->parseCircle(child);
            vec.push_back(circle);
        }
        else if (shapeName == "ellipse"){
            RawElement* ellip = this->parseEllipse(child);
            vec.push_back(ellip);
        }
        else if (shapeName == "polygon"){
            RawElement* polygon = this->parsePolygon(child);
            vec.push_back(polygon);
        }
        else if (shapeName == "polyline"){
            RawElement* polyline = this->parsePolyline(child);
            vec.push_back(polyline);
        }
        else if (shapeName == "line"){
            RawElement* line = this->parseLine(child);
            vec.push_back(line);
        }
        else if (shapeName == "g") {
            RawElement* group = this->parseGroup(child, doc);
            vec.push_back(group);
        }
        else if (shapeName == "path") {
            RawElement* path = this->parsePath(child);
            vec.push_back(path);
        }
        else if (child->value()) {
            RawElement* text = this->parseText(child);
            vec.push_back(text);
        }
    }
    
    return new Group(vec, stroke, fill, transform);
}

bool GetSVG::checkAlpha(char ch){
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'); 
}

void GetSVG::standardizeString(std::string& s){
    std::replace(s.begin(), s.end(), ',', ' ');
    int n = s.size();
    // Case: Command with no space at first
    if (n > 1 && checkAlpha(s[0]) && s[1] != ' '){
        s.insert(s.begin() + 1, ' ');
        n++;
    }
    for (int i = 1; i < n; i++){
        // It will always start with something else than '-' so no segmentation fault
        if ((s[i] == '-') && s[i - 1] != ' '){
            s.insert(s.begin() + i, ' ');
            i++;
            n++;
        }
        else if (checkAlpha(s[i])){
            int curPos = i;
            if (s[curPos + 1] != ' '){
                s.insert(s.begin() + curPos + 1, ' ');
                i++;
                n++;
            }
            if (s[curPos - 1] != ' '){
                s.insert(s.begin() + curPos, ' ');
                i++;
                n++;
            }
        }
    }
}

std::vector<std::pair<char, Gdiplus::PointF>> GetSVG::parsePathData(rapidxml::xml_attribute<> *attr){
    std::vector<std::pair<char, Gdiplus::PointF>> pathData;
    std::string d = attr->value();
    standardizeString(d);
    std::stringstream ss(d);
    std::string val;
    char curCommand = 'M'; // Init default value
    while (ss >> val){
        if (checkAlpha(val[0])){
            curCommand = val[0];
            if (curCommand == 'M' || curCommand == 'm' || curCommand == 'L' || curCommand == 'l'){
                double x, y;
                ss >> x >> y;
                pathData.push_back(std::make_pair(curCommand, Gdiplus::PointF(x, y)));
            }
            else if (curCommand == 'C' || curCommand == 'c'){
                double x, y;
                for (int i = 0; i < 3; i++){
                    ss >> x >> y;
                    pathData.push_back(std::make_pair(curCommand, Gdiplus::PointF(x, y)));
                }
            }
            else if (curCommand == 'H' || curCommand == 'h' || curCommand == 'V' || curCommand == 'v') {
                double stat;
                ss >> stat;
                if (curCommand == 'H' || curCommand == 'h') {
                    pathData.push_back(std::make_pair(curCommand, Gdiplus::PointF(stat, 0)));
                }
                else {
                    pathData.push_back(std::make_pair(curCommand, Gdiplus::PointF(0, stat)));
                }
            }
            else if (curCommand == 'Z' || curCommand == 'z') {
                pathData.push_back(std::make_pair(curCommand, Gdiplus::PointF(0, 0)));
            }
        }
        else{
            if (curCommand == 'M' || curCommand == 'm' || curCommand == 'L' || curCommand == 'l'){
                if (curCommand == 'M' || curCommand == 'm'){
                    curCommand--;
                }
                double x, y;
                x = stod(val);
                ss >> y;
                pathData.push_back(std::make_pair(curCommand, Gdiplus::PointF(x, y)));
            }
            else if (curCommand == 'C' || curCommand == 'c'){
                double x, y;
                for (int i = 0; i < 3; i++){
                    if (i != 0){
                        ss >> x >> y;
                    }
                    else{
                        x = stod(val);
                        ss >> y;
                    }
                    pathData.push_back(std::make_pair(curCommand, Gdiplus::PointF(x, y)));
                }
            }
            else if (curCommand == 'H' || curCommand == 'h' || curCommand == 'V' || curCommand == 'v') {
                double stat;
                stat = stod(val);
                if (curCommand == 'H' || curCommand == 'h') {
                    pathData.push_back(std::make_pair(curCommand, Gdiplus::PointF(stat, 0)));
                }
                else {
                    pathData.push_back(std::make_pair(curCommand, Gdiplus::PointF(0, stat)));
                }
            }
        }
    }
    return pathData;
}

RawElement* GetSVG::parsePath(rapidxml::xml_node<> *node) {
    Stroke stroke = parseStroke(node->first_attribute());
    Fill fill = parseFill(node->first_attribute());
    Transform transform;

    for (rapidxml::xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
        std::string attrName = attr->name();
        std::string attrValue = attr->value();

        if (attrName == "transform") {
            transform = parseTransform(attrValue);
        }
    }

    rapidxml::xml_attribute<> *d_attr = node->first_attribute("d");
    std::vector<std::pair<char, Gdiplus::PointF>> pathData;

    if (d_attr){
        pathData = parsePathData(d_attr);
    }

    return new Path(pathData, stroke, fill, transform);
}

std::vector<RawElement*> GetSVG::parseSVGFile(const std::string& filePath){
    std::vector<RawElement*> vec;
    std::ifstream svgFile(filePath);
    if (!svgFile) {
        std::cout << "Error: Could not open SVG file.\n";
        return vec;
    }

    std::string svgContent((std::istreambuf_iterator<char>(svgFile)), std::istreambuf_iterator<char>());
    
    rapidxml::xml_document<> doc;

    char* xml = new char[svgContent.size() + 1];
    std::strcpy(xml, svgContent.c_str());

    doc.parse<0>(xml);

    rapidxml::xml_node<> *root = doc.first_node("svg");
    if (root){
        for (rapidxml::xml_node<> *child = root->first_node(); child; child = child->next_sibling()) {
            std::string shapeName = child->name();
            if (shapeName == "rect"){
                RawElement* rect = this->parseRect(child);
                vec.push_back(rect);
            }
            else if (shapeName == "circle"){
                RawElement* circle = this->parseCircle(child);
                vec.push_back(circle);
            }
            else if (shapeName == "ellipse"){
                RawElement* ellip = this->parseEllipse(child);
                vec.push_back(ellip);
            }
            else if (shapeName == "polygon"){
                RawElement* polygon = this->parsePolygon(child);
                vec.push_back(polygon);
            }
            else if (shapeName == "polyline"){
                RawElement* polyline = this->parsePolyline(child);
                vec.push_back(polyline);
            }
            else if (shapeName == "line"){
                RawElement* line = this->parseLine(child);
                vec.push_back(line);
            }
            else if (shapeName == "g") {
                RawElement* group = this->parseGroup(child, doc);
                vec.push_back(group);
            }
            else if (shapeName == "path") {
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
    return vec;
}