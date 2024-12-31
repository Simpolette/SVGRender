#include "Stroke.h"

Stroke::Stroke(){
    this->color = Gdiplus::Color(0, 0, 0);
    this->width = 1;
    this->opacity = 1;
    this->linecap = "butt";
    this->dasharray.clear();
    this->linejoin = "miter";
    this->miterlimit = 4;
}

Stroke::Stroke(std::string color, double width, double opacity, std::string linecap, std::vector<double> dasharray, std::string linejoin, double miterlimit){
    SVGColor fillColor(color);
    this->color = Gdiplus::Color(fillColor.getR(), fillColor.getG(), fillColor.getB());
    this->width = width;
    this->opacity = opacity;
    this->linecap = linecap;
    this->dasharray.clear();
    this->linejoin = linejoin;
    this->miterlimit = miterlimit;

    if (color != ""){
        this->opacity = 1;
    }
    
}

Gdiplus::Pen* Stroke::getPen() const {
    Gdiplus::Color penColor(
        static_cast<BYTE>(opacity * 255), // Độ trong suốt (alpha)
        color.GetRed(),
        color.GetGreen(),
        color.GetBlue()
    );

    Gdiplus::Pen* pen = new Gdiplus::Pen(penColor, static_cast<Gdiplus::REAL>(width));
    
    pen->SetLineJoin(Gdiplus::LineJoinMiter);
    pen->SetMiterLimit(miterlimit);

    return pen;
}

void Stroke::print() const{
    std::cout << "Stroke:\n"; 
    std::cout << "Color: (" << (int)color.GetR() << ", " 
                            << (int)color.GetG() << ", " 
                            << (int)color.GetB() << ")\n";
    std::cout << "Opacity: " << opacity << "\n";
    std::cout << "Width: " << width << "\n";
    std::cout << "Mitter limit: " << miterlimit << "\n";
}

void Stroke::convertFromStyle(const std::string &style){
    size_t pos = 0;
    std::string color;

    while (pos < style.length()) {
        size_t key_end = style.find(':', pos);
        size_t value_end = style.find(';', key_end);

        if (key_end == std::string::npos) {
            break;
        }
        if (value_end == std::string::npos) {
            value_end = style.length();
        }

        std::string key = style.substr(pos, key_end - pos);
        std::string value = style.substr(key_end + 1, value_end - key_end - 1);

        key.erase(0, key.find_first_not_of(" \t"));
        key.erase(key.find_last_not_of(" \t") + 1);
        value.erase(0, value.find_first_not_of(" \t"));
        value.erase(value.find_last_not_of(" \t") + 1);
        if (key == "stroke") {
            color = value;
            for (int i = 0; i < color.size(); i++){
                color[i] = std::tolower(color[i]);
            }
            if (color.find("none") != std::string::npos){
                opacity = 0;
                color = "";
                break;
            }
        }
        else if (key == "stroke-width"){
            width = stod(value);
            if (width == 0){
                opacity = 0;
                color = "";
                break;
            }
        }
        else if (key == "stroke-opacity"){
            opacity = stod(value);
        }
        else if (key == "stroke-miterlimit"){
            miterlimit = stod(value);
        }
        else if (key == "stroke-linecap"){
            linecap = value;
        }
        else if (key == "stroke-dasharray"){
            //Stroke_dasharray
        }
        else if (key == "stroke-linejoin"){
            linejoin = value;
        }

        if (value_end == std::string::npos) {
            pos = std::string::npos;
        }
        else {
            pos = value_end + 1;
        }
    }
    SVGColor fillColor(color);
    this->color = Gdiplus::Color(fillColor.getR(), fillColor.getG(), fillColor.getB());
}
