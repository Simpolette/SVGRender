#include "Transform.h"

Transform::Transform(std::vector<std::pair<std::string, std::string>> transforms) {
    this->transforms = transforms;
}

Transform::Transform() {
    
}

Gdiplus::Matrix* Transform::getMatrix() const {
    Gdiplus::Matrix* matrix = new Gdiplus::Matrix;

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

void Transform::print() const{
    std::cout << "Transform:\n"; 
    for (int i = 0; i < transforms.size(); i++){
        std::cout << transforms[i].first << ": " << transforms[i].second << "\n";
    }
}