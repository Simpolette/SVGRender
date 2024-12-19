#include "Renderer.h"
using namespace std;
Renderer::Renderer(const Fill& fill, const Stroke& stroke, const Transform& transform){
    pen = getPen(stroke);
    brush = getBrush(fill);
    matrix = getMatrix(transform);
}

Gdiplus::Pen* Renderer::getPen(const Stroke& stroke) {
    Gdiplus::Color color = stroke.getColorA();
    Gdiplus::Color penColor(
        static_cast<BYTE>(stroke.getOpacity() * 255), // Độ trong suốt (alpha)
        color.GetRed(),
        color.GetGreen(),
        color.GetBlue()
    );

    Gdiplus::Pen* pen = new Gdiplus::Pen(penColor, static_cast<Gdiplus::REAL>(stroke.getWidth()));
    
    pen->SetLineJoin(Gdiplus::LineJoinMiter);
    pen->SetMiterLimit(stroke.getMiterLimit());

    return pen;
}

Gdiplus::Brush* Renderer::getBrush(const Fill& fill) {
    Gdiplus::Color color = fill.getColorA();
    Gdiplus::Color brushColor(
        static_cast<BYTE>(fill.getOpacity() * 255), 
        color.GetRed(),
        color.GetGreen(),
        color.GetBlue()
    );

    Gdiplus::Brush* brush = new Gdiplus::SolidBrush(brushColor);    

    return brush;
}

Gdiplus::Matrix* Renderer::getMatrix(const Transform& transform){
    Gdiplus::Matrix* matrix = new Gdiplus::Matrix;

    std::vector<std::pair<std::string, std::string>> transforms = transform.getTransforms();
    for (int i = 0; i < transforms.size(); i++){
        std::string type = transforms[i].first;
        std::stringstream ss(transforms[i].second);

        if (type == "translate"){
            double x, y;
            ss >> x >> y;

            matrix->Translate(x, y);
        }
        else if (type == "scale"){
            int cnt;
            double x, y;
            ss >> cnt;
            if (cnt >= 1){
                ss >> x;
                y = x;
            }
            if (cnt >= 2){
                ss >> y;
            }

            matrix->Scale(x, y);
        }
        else if (type == "rotate"){
            int cnt;
            double rotate;
            double x = 0, y = 0;
            ss >> cnt;
            if (cnt >= 1){
                ss >> rotate;
            }
            if (cnt >= 3){
                ss >> x >> y;
            }
            matrix->RotateAt(rotate, Gdiplus::PointF(x, y));
        }
        else if (type == "matrix"){
            double a, b, c, d, e, f;
            ss >> a >> b >> c >> d >> e >> f;
            Gdiplus::Matrix mulMatrix(a, b, c, d, e, f);
            matrix->Multiply(&mulMatrix);
        }
    }

    return matrix;
}

Renderer::~Renderer(){
    delete pen;
    delete brush;
    delete matrix;
}