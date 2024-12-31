#include "SVG.h"

Stroke GetSVG::parseStroke(rapidxml::xml_attribute<> *attr){
    std::string color = "";
    int width = 1;
    double opacity = 0;
    std::string linecap = "butt";
    std::vector<double> dasharray;
    std::string linejoin = "miter";
    double miterlimit = 4;
    
    for (;attr ;attr = attr->next_attribute()){
        std::string attrName = attr->name();
        std::string attrValue = attr->value();

        if (attrName == "stroke") {
            color = attrValue;
            for (int i = 0; i < color.size(); i++){
                color[i] = std::tolower(color[i]);
            }
            if (color.find("none") != std::string::npos){
                opacity = 0;
                color = "";
                break;
            }
        }
        else if (attrName == "stroke-width"){
            width = stod(attrValue);
            if (width == 0){
                opacity = 0;
                color = "";
                break;
            }
        }
        else if (attrName == "stroke-opacity"){
            opacity = stod(attrValue);
        }
        else if (attrName == "stroke-miterlimit"){
            miterlimit = stod(attrValue);
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

    return Stroke(color, width, opacity, linecap, dasharray, linejoin, miterlimit);
}

Fill GetSVG::parseFill(rapidxml::xml_attribute<> *attr){
    std::string color = "";
    double opacity = 1;
    std::string rule = "nonezero";
    std::string id;
    
    for (;attr ;attr = attr->next_attribute()){
        std::string attrName = attr->name();
        std::string attrValue = attr->value();

        if (attrName == "fill"){
            color = attrValue;
            if (color.find("url") != std::string::npos){
                // Handle color id
                if (color.find("'") != std::string::npos) {
                    id = color.substr(color.find("'") + 1);
                    id.erase(id.find("'"));
                    id.erase(id.find("#"), 1);
                } 
                else{
                    id = color.substr(color.find("#") + 1);
                    id.erase(id.find(")"));
                }
            }
            else{
                for (int i = 0; i < color.size(); i++){
                    color[i] = std::tolower(color[i]);
                }
                if (color.find("none") != std::string::npos){
                    opacity = 0;
                    color = "";
                    break;
                }
            }
        }
        else if (attrName == "fill-opacity"){
            opacity = stod(attrValue);
        }
        else if (attrName == "fill-rule"){
            rule = attrValue;
        }
    }

    Gradient* gradient = NULL;
    if (gradients.find(id) != gradients.end()){
        gradient = gradients[id];
    }

    return Fill(color, opacity, rule, gradient);
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
        if (attrValue[i] == ' ' && (checkNumber(attrValue[i + 1]) || attrValue[i + 1] == '.')){
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
    std::vector<std::pair<std::string, std::string>> transforms;
    
    while (getline(ss, transform, ')')){
        std::istringstream ss2(transform);
        std::string attrName;
        std::string attrValue;
        
        getline(ss2, attrName, '(');
        getline(ss2, attrValue, ')');
        standardizeString(attrValue);
                
        int cnt = countAttrVal(attrValue);

        if (attrName.find("translate") != std::string::npos){
            attrName = "translate";
        }
        else if (attrName.find("scale") != std::string::npos){
            attrName = "scale";
            attrValue = std::to_string(cnt) + " " + attrValue;
        }
        else if (attrName.find("rotate") != std::string::npos){
            attrName = "rotate";
            attrValue = std::to_string(cnt) + " " + attrValue;
        }
        else if (attrName.find("matrix") != std::string::npos){
            attrName = "matrix";
        }
        transforms.push_back(std::make_pair(attrName, attrValue));
    }

    return Transform(transforms);
}

void GetSVG::parseStyle(const std::string &style, Stroke& stroke, Fill& fill) {
    std::string id = "";
    stroke.convertFromStyle(style);
    fill.convertFromStyle(style, id);
    Gradient* gradient = NULL;
    if (gradients.find(id) != gradients.end()){
        gradient = gradients[id];
    }
    fill.setGradient(gradient);
}

RawElement* GetSVG::parseRect(rapidxml::xml_node<> *node){
    double x = 0, y = 0, width = 0, height = 0;

    Stroke stroke = parseStroke(node->first_attribute());
    Fill fill = parseFill(node->first_attribute());
    
    rapidxml::xml_attribute<>* style_attr = node->first_attribute("style");
    if (style_attr) {
        std::string style = style_attr->value();
        parseStyle(style, stroke, fill);
    } 

    rapidxml::xml_attribute<>* class_attr = node->first_attribute("class");
    if (class_attr){
        std::string classID = class_attr->value();
        if (styleSheet.find(classID) != styleSheet.end()){
            fill = styleSheet[classID];
        }
    }

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
            width = stod(attrValue);
        }
        else if (attrName == "height"){
            height = stod(attrValue);
        }
    }
    return new Rectan(Gdiplus::PointF(x, y), width, height, stroke, fill, transform);
}

RawElement* GetSVG::parseCircle(rapidxml::xml_node<> *node){
    double x = 0, y = 0, radius = 0;
    Stroke stroke = parseStroke(node->first_attribute());
    Fill fill = parseFill(node->first_attribute());
    
    rapidxml::xml_attribute<>* style_attr = node->first_attribute("style");
    if (style_attr) {
        std::string style = style_attr->value();
        parseStyle(style, stroke, fill);
    } 

    rapidxml::xml_attribute<>* class_attr = node->first_attribute("class");
    if (class_attr){
        std::string classID = class_attr->value();
        if (styleSheet.find(classID) != styleSheet.end()){
            fill = styleSheet[classID];
        }
    }

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
            radius = stod(attrValue);
        }
    }
    return new Circle(Gdiplus::PointF(x, y), radius, stroke, fill, transform);
}

RawElement* GetSVG::parseEllipse(rapidxml::xml_node<> *node){
    double x = 0, y = 0, rx = 0, ry = 0;
    Stroke stroke = parseStroke(node->first_attribute());
    Fill fill = parseFill(node->first_attribute());
    
    rapidxml::xml_attribute<>* style_attr = node->first_attribute("style");
    if (style_attr) {
        std::string style = style_attr->value();
        parseStyle(style, stroke, fill);
    }

    rapidxml::xml_attribute<>* class_attr = node->first_attribute("class");
    if (class_attr){
        std::string classID = class_attr->value();
        if (styleSheet.find(classID) != styleSheet.end()){
            fill = styleSheet[classID];
        }
    }

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
            rx = stod(attrValue);
        }
        else if (attrName == "ry"){
            ry = stod(attrValue);
        }
    }

    return new Ellip(Gdiplus::PointF(x, y), rx, ry, stroke, fill, transform);
}

RawElement* GetSVG::parsePolygon(rapidxml::xml_node<> *node){
    std::string points = "";

    Stroke stroke = parseStroke(node->first_attribute());
    Fill fill = parseFill(node->first_attribute());
    
    rapidxml::xml_attribute<>* style_attr = node->first_attribute("style");
    if (style_attr) {
        std::string style = style_attr->value();
        parseStyle(style, stroke, fill);
    }

    rapidxml::xml_attribute<>* class_attr = node->first_attribute("class");
    if (class_attr){
        std::string classID = class_attr->value();
        if (styleSheet.find(classID) != styleSheet.end()){
            fill = styleSheet[classID];
        }
    }

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
    
    rapidxml::xml_attribute<>* style_attr = node->first_attribute("style");
    if (style_attr) {
        std::string style = style_attr->value();
        parseStyle(style, stroke, fill);
    } 

    rapidxml::xml_attribute<>* class_attr = node->first_attribute("class");
    if (class_attr){
        std::string classID = class_attr->value();
        if (styleSheet.find(classID) != styleSheet.end()){
            fill = styleSheet[classID];
        }
    }
    
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
    
    rapidxml::xml_attribute<>* style_attr = node->first_attribute("style");
    if (style_attr) {
        std::string style = style_attr->value();
        parseStyle(style, stroke, fill);
    }

    rapidxml::xml_attribute<>* class_attr = node->first_attribute("class");
    if (class_attr){
        std::string classID = class_attr->value();
        if (styleSheet.find(classID) != styleSheet.end()){
            fill = styleSheet[classID];
        }
    }

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
    std::string content = standardizeText(node->value());
    double font_size = 16;
    double x = 0, y = 0;
    std::string font_family = "Times New Roman";
    std::string font_style = "normal";
    std::string text_anchor = "start";
    std::string font_weight = "normal";
    Stroke stroke = parseStroke(node->first_attribute());
    Fill fill = parseFill(node->first_attribute());
    
    rapidxml::xml_attribute<>* style_attr = node->first_attribute("style");
    if (style_attr) {
        std::string style = style_attr->value();
        parseStyle(style, stroke, fill);
    } 

    rapidxml::xml_attribute<>* class_attr = node->first_attribute("class");
    if (class_attr){
        std::string classID = class_attr->value();
        if (styleSheet.find(classID) != styleSheet.end()){
            fill = styleSheet[classID];
        }
    }

    Transform transform;

    for (rapidxml::xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
        std::string attrName = attr->name();
        std::string attrValue = attr->value();

        if (attrName == "transform") {
            transform = parseTransform(attrValue);
        }
        else if (attrName == "x"){
            x = getDoubleValue(attrValue);
            if (attrValue.find('%') != std::string::npos){
                x = boxOrigin.X + x * boxWidth;
            }
        }
        else if (attrName == "y"){
            y = getDoubleValue(attrValue);
            if (attrValue.find('%') != std::string::npos){
                y = boxOrigin.Y + y * boxHeight;
            }
        }
        else if (attrName == "font-size"){
            font_size = stod(attrValue);
        }
        else if (attrName == "font-family"){
            font_family = attrValue;
        }
        else if (attrName == "font-style"){
            font_style = attrValue;
        }
        else if (attrName == "text-anchor"){
            text_anchor = attrValue;
        }
        else if (attrName == "font-weight"){
            font_weight = attrValue;
        }
    }

    return new Text(content, Gdiplus::PointF(x, y), font_size, font_family, font_style, font_weight, text_anchor, stroke, fill, transform);
}

RawElement* GetSVG::parseGroup(rapidxml::xml_node<> *node, rapidxml::xml_document<>& doc) {
    Stroke stroke = parseStroke(node->first_attribute());
    Fill fill = parseFill(node->first_attribute());
    
    rapidxml::xml_attribute<>* style_attr = node->first_attribute("style");
    if (style_attr) {
        std::string style = style_attr->value();
        parseStyle(style, stroke, fill);
    }

    rapidxml::xml_attribute<>* class_attr = node->first_attribute("class");
    if (class_attr){
        std::string classID = class_attr->value();
        if (styleSheet.find(classID) != styleSheet.end()){
            fill = styleSheet[classID];
        }
    }

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
                if (inheritAttr[i].first == attr->name()){
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

bool GetSVG::checkCommand(char ch){
    ch = std::tolower(ch);
    return (ch == 'm' || ch == 'l' || ch == 'h' || ch == 'v' || ch == 'c'
        || ch == 's' || ch == 'q' || ch == 't' || ch == 'a' || ch == 'z'); 
}

std::string GetSVG::standardizeText(std::string text){
    std::replace(text.begin(), text.end(), '\t', ' ');
    std::replace(text.begin(), text.end(), '\n', ' ');
    
    std::string s = "";
    int n = text.size();
    bool isPrevSpace = false;
    if (n > 1 && text[0] == ' '){
        isPrevSpace = true;
    }
    for (int i = 0; i < n; i++){
        if (text[i] == ' '){
            if (!isPrevSpace){
                s += text[i];
                isPrevSpace = true;
            }
        }
        else{
            s += text[i];
            isPrevSpace = false;
        }
    }
    
    return s;
}


void GetSVG::standardizeString(std::string& s){
    std::replace(s.begin(), s.end(), ',', ' ');
    int n = s.size();
    bool isPrevComma = false;
    // Case: Command with no space at first
    if (n > 1){
        if (checkCommand(s[0]) && s[1] != ' '){
            s.insert(s.begin() + 1, ' ');
            n++;
        }
        else if (s[0] == '.'){
            isPrevComma = true;
        }
    }
    for (int i = 1; i < n; i++){
        // It will always start with something else than '-' so no segmentation fault
        if ((s[i] == '-') && s[i - 1] != ' ' && std::tolower(s[i - 1]) != 'e'){
            isPrevComma = false;
            s.insert(s.begin() + i, ' ');
            i++;
            n++;
        }
        else if (checkCommand(s[i])){
            isPrevComma = false;
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
        else if (s[i] == ' '){
            isPrevComma = false;
        }
        else if (s[i] == '.'){
            int curPos = i;
            if (isPrevComma){
                s.insert(s.begin() + curPos, ' ');
                i++;
                n++;
            }
            else{
                isPrevComma = true;
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
        if (checkCommand(val[0])){
            curCommand = val[0];
            if (curCommand == 'M' || curCommand == 'm' || curCommand == 'L' || curCommand == 'l' || curCommand == 'T' || curCommand == 't'){
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
            else if (curCommand == 'H' || curCommand == 'h' || curCommand == 'V' || curCommand == 'v'){
                double stat;
                ss >> stat;
                if (curCommand == 'H' || curCommand == 'h') {
                    pathData.push_back(std::make_pair(curCommand, Gdiplus::PointF(stat, 0)));
                }
                else {
                    pathData.push_back(std::make_pair(curCommand, Gdiplus::PointF(0, stat)));
                }
            }
            else if (curCommand == 'S' || curCommand == 's' || curCommand == 'Q' || curCommand == 'q'){
                double x, y;
                for (int i = 0; i < 2; i++){
                    ss >> x >> y;
                    pathData.push_back(std::make_pair(curCommand, Gdiplus::PointF(x, y)));
                }
            }
            else if (curCommand == 'A' || curCommand == 'a'){
                double x, y;
                for (int i = 0; i < 4; i++){
                    if (i != 1){
                        ss >> x >> y;
                    }
                    else{
                        ss >> x;
                        y = 0;
                    }
                    pathData.push_back(std::make_pair(curCommand, Gdiplus::PointF(x, y)));
                }
            }
            else if (curCommand == 'Z' || curCommand == 'z'){
                pathData.push_back(std::make_pair(curCommand, Gdiplus::PointF(0, 0)));
            }
        }
        else{
            if (curCommand == 'M' || curCommand == 'm' || curCommand == 'L' || curCommand == 'l' || curCommand == 'T' || curCommand == 't'){
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
            else if (curCommand == 'S' || curCommand == 's' || curCommand == 'Q' || curCommand == 'q'){
                double x, y;
                for (int i = 0; i < 2; i++){
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
            else if (curCommand == 'A' || curCommand == 'a'){
                double x, y;
                x = stod(val);
                ss >> y;
                pathData.push_back(std::make_pair(curCommand, Gdiplus::PointF(x, y)));
                double xAxisRotation;
                ss >> xAxisRotation;
                pathData.push_back(std::make_pair(curCommand, Gdiplus::PointF(xAxisRotation, 0)));
                double largeArc, sweep;
                ss >> largeArc >> sweep;
                pathData.push_back(std::make_pair(curCommand, Gdiplus::PointF(largeArc, sweep)));
                ss >> x >> y;
                pathData.push_back(std::make_pair(curCommand, Gdiplus::PointF(x, y)));
            }
        }
    }
    return pathData;
}

RawElement* GetSVG::parsePath(rapidxml::xml_node<> *node) {
    Stroke stroke = parseStroke(node->first_attribute());
    Fill fill = parseFill(node->first_attribute());
    
    rapidxml::xml_attribute<>* style_attr = node->first_attribute("style");
    if (style_attr){
        std::string style = style_attr->value();
        parseStyle(style, stroke, fill);
    }

    rapidxml::xml_attribute<>* class_attr = node->first_attribute("class");
    if (class_attr){
        std::string classID = class_attr->value();
        if (styleSheet.find(classID) != styleSheet.end()){
            fill = styleSheet[classID];
        }
    }

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

double GetSVG::getDoubleValue(const std::string &s) {
    if (s.find('%') != std::string::npos) {
        return stod(s.substr(0, s.find('%'))) / 100;
    }
    return stod(s);
}

void GetSVG::parseStyleSheet(rapidxml::xml_node<> *defs){
    for (rapidxml::xml_node<>* node = defs->first_node("style"); node; node = node->next_sibling("style")){
        std::stringstream styleVal(node->value());
        std::string classAttr;
        while (getline(styleVal, classAttr, '}')){
            Fill fill;
            Stroke stroke;

            size_t startID = classAttr.find('.') + 1;
            std::string id = classAttr.substr(startID, classAttr.find('{') - startID);
            
            std::string classAttrVal = classAttr.substr(classAttr.find('{') + 1);
            parseStyle(classAttrVal, stroke, fill);
            styleSheet[id] = fill;
        }
    }
}

void GetSVG::parseGradient(rapidxml::xml_node<> *defs) {
    for (rapidxml::xml_node<>* node = defs->first_node(); node; node = node->next_sibling()) {
        std::string type = node->name();
        if (type == "linearGradient" || type == "radialGradient"){
            std::string id;
            std::string units = "objectBoundingBox";
            Transform transform;
            std::string spreadMethod = "pad";
            std::vector<Stop> stops;
            
            rapidxml::xml_attribute<>* idAttr = node->first_attribute("id");
            if (idAttr){
                id = idAttr->value();
            }
            rapidxml::xml_attribute<>* href = node->first_attribute("xlink:href");
            if (href){
                std::string attrVal = href->value();
                std::string idCopy;
                if (attrVal.find("'") != std::string::npos) {
                    idCopy = attrVal.substr(attrVal.find("'") + 1);
                    idCopy.erase(idCopy.find("'"));
                    idCopy.erase(idCopy.find("#"), 1);
                } 
                else{
                    idCopy = attrVal.substr(attrVal.find("#") + 1);
                }
                if (gradients.find(idCopy) != gradients.end()){
                    units = gradients[idCopy]->getUnits();
                    spreadMethod = gradients[idCopy]->getSpreadMethod();
                    stops = gradients[idCopy]->getStops();
                    transform = gradients[idCopy]->getTransform();
                } 
            }

            for (rapidxml::xml_attribute<>* attr = node->first_attribute(); attr; attr = attr->next_attribute()){
                std::string attrName = attr->name();
                std::string attrValue = attr->value();

                if (attrName == "gradientUnits") {
                    units = attrValue;
                }
                else if (attrName == "gradientTransform") {
                    transform = parseTransform(attrValue);
                }
                else if (attrName == "spreadMethod") {
                    spreadMethod = attrValue;
                }
            }
            if (node->first_node("stop")){
                stops.clear();
            }

            for (rapidxml::xml_node<>* childNode = node->first_node("stop"); childNode; childNode = childNode->next_sibling("stop")) {
                std::string color = "";
                double offset = 0;
                double opacity = 1;

                for (rapidxml::xml_attribute<>* attr = childNode->first_attribute(); attr; attr = attr->next_attribute()) {
                    std::string attrName = attr->name();
                    std::string attrValue = attr->value();
                    if (attrName == "offset"){
                        offset = getDoubleValue(attrValue);
                    }
                    else if (attrName == "stop-color"){
                        color = attrValue;
                    }
                    else if (attrName == "stop-opacity"){
                        opacity = getDoubleValue(attrValue);
                    }
                }

                Stop stop(offset, color, opacity);
                rapidxml::xml_attribute<>* style_attr = childNode->first_attribute("style");
                if (style_attr) {
                    std::string style = style_attr->value();
                    stop.convertFromStyle(style);
                } 
                stops.push_back(stop);
            }

            Gradient* gradient;

            if (type == "linearGradient"){
                double x1 = 0, y1 = 0, x2 = 1, y2 = 0;

                for (rapidxml::xml_attribute<>* attr = node->first_attribute(); attr; attr = attr->next_attribute()){
                    std::string attrName = attr->name();
                    std::string attrValue = attr->value();
                    
                    if (attrName == "x1") {
                        x1 = getDoubleValue(attrValue);
                    }
                    else if (attrName == "x2") {
                        x2 = getDoubleValue(attrValue);
                    }
                    else if (attrName == "y1") {
                        y1 = getDoubleValue(attrValue);
                    }
                    else if (attrName == "y2") {
                        y2 = getDoubleValue(attrValue);
                    }
                }

                gradient = new LinearGradient(units, transform, spreadMethod, stops, Gdiplus::PointF(x1, y1), Gdiplus::PointF(x2, y2));
            }
            else if (type == "radialGradient"){
                double cx = 0.5, cy = 0.5, r = 0.5, fx = 0, fy = 0, fr = 0;
                
                for (rapidxml::xml_attribute<>* attr = node->first_attribute(); attr; attr = attr->next_attribute()){
                    std::string attrName = attr->name();
                    std::string attrValue = attr->value();
                    
                    if (attrName == "cx") {
                        cx = getDoubleValue(attrValue);
                    }
                    else if (attrName == "cy") {
                        cy = getDoubleValue(attrValue);
                    }
                    else if (attrName == "r") {
                        r = getDoubleValue(attrValue);
                    }
                    else if (attrName == "fx") {
                        fx = getDoubleValue(attrValue);
                    }
                    else if (attrName == "fy") {
                        fy = getDoubleValue(attrValue);
                    }
                    else if (attrName == "fr") {
                        fr = getDoubleValue(attrValue);
                    }
                }
                if (fx == 0){
                    fx = cx;
                }
                if (fy == 0){
                    fy = cy;
                }

                gradient = new RadialGradient(units, transform, spreadMethod, stops, Gdiplus::PointF(cx, cy), r, Gdiplus::PointF(fx, fy), fr);  
            }
            gradients[id] = gradient;
        }
    }
}

void GetSVG::parseDefs(rapidxml::xml_node<> *defs){
    if (!defs) {
        return;
    }
    this->parseStyleSheet(defs);
    this->parseGradient(defs);
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

    viewWidth = 0;
    viewHeight = 0;
    boxOrigin = Gdiplus::PointF(0, 0);
    boxWidth = 0;
    boxHeight = 0;

    for (rapidxml::xml_attribute<>* attr = root->first_attribute(); attr; attr = attr->next_attribute()){
        std::string attrName = attr->name();
        std::string attrValue = attr->value();
        if (attrName == "width"){
            if (attrValue.find("pt") != std::string::npos){
                size_t idx = 0;
                viewWidth = stod(attrValue, &idx) * 4 / 3;
            }
            else{
                viewWidth = stod(attrValue);
            }
        }
        else if (attrName == "height"){
            if (attrValue.find("pt") != std::string::npos){
                size_t idx = 0;
                viewHeight = stod(attrValue, &idx) * 4 / 3;
            }
            else{
                viewHeight = stod(attrValue);
            }
        }
        else if (attrName == "viewBox"){
            std::stringstream ss(attrValue);
            double x, y;
            ss >> x >> y >> boxWidth >> boxHeight;
            boxOrigin = Gdiplus::PointF(x, y);
        }

    }

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
            else if (shapeName == "g"){
                RawElement* group = this->parseGroup(child, doc);
                vec.push_back(group);
            }
            else if (shapeName == "path"){
                RawElement* path = this->parsePath(child);
                vec.push_back(path);
            }
            else if (shapeName == "defs"){
                this->parseDefs(child);
            }
            else if (shapeName == "text"){
                RawElement* text = this->parseText(child);
                vec.push_back(text);
            }
        }
    }

    delete[] xml;
    return vec;
}

double GetSVG::getViewWidth() const{
    return viewWidth;
}

double GetSVG::getViewHeight() const{
    return viewHeight;
}

Gdiplus::PointF GetSVG::getBoxOrigin() const{
    return boxOrigin;
}

double GetSVG::getBoxWidth() const{
    return boxWidth;
}

double GetSVG::getBoxHeight() const{
    return boxHeight;
}

GetSVG::~GetSVG(){
    for (auto& [id, gradient] : gradients) {
        delete gradient;
    }
}

