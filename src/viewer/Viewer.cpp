#include "Viewer.h"

Viewer::Viewer(){
    this->scale = 1;
    this->width = 0;
    this->height = 0;
    this->center = Gdiplus::PointF(0, 0);
    this->boxWidth = 0;
    this->boxHeight = 0;
    this->boxOrigin = Gdiplus::PointF(0, 0);
    this->rotateAngle = 0;
}

Viewer::~Viewer(){
    for (int i = 0; i < elements.size(); i++){
        delete elements[i];
    }
}

void Viewer::addRenderer(Renderer* renderer){
    elements.push_back(renderer);
}

void Viewer::render(Gdiplus::Graphics& graphics){
    for (int i = 0; i < elements.size(); i++){
        elements[i]->render(graphics);
    }
}

void Viewer::setCenter(Gdiplus::PointF center){
    this->center = center;
}

void Viewer::setBoxWidth(double boxWidth){
    this->boxWidth = boxWidth;
}

void Viewer::setBoxHeight(double boxHeight){
    this->boxHeight = boxHeight;
}

void Viewer::setBoxOrigin(Gdiplus::PointF boxOrigin){
    this->boxOrigin = boxOrigin;
}

void Viewer::setViewPort(HDC hdc){
    RECT clientRect;
    GetClientRect(WindowFromDC(hdc), &clientRect);
    width = clientRect.right - clientRect.left;
    height = clientRect.bottom - clientRect.top;
    center = Gdiplus::PointF(width / 2, height / 2);
    if (boxHeight == 0 && boxWidth == 0){
        boxWidth = width;
        boxHeight = height;
    }
}

void Viewer::zoom(int delta){
    if (delta > 0){
        scale *= 1.1; // Zoom in
    }
    else {
        scale /= 1.1; // Zoom out
    }
}

void Viewer::rotateLeft(){
    rotateAngle -= 1;
    if (rotateAngle < 0){
        rotateAngle += 360;
    }
}

void Viewer::rotateRight(){
    rotateAngle += 1;
    if (rotateAngle >= 360){
        rotateAngle -= 360;
    }
}

Gdiplus::Matrix* Viewer::getViewBoxMatrix(){
    double scaleX = width / boxWidth;
    double scaleY = height / boxHeight;
    double uniformScale = std::min(scaleX, scaleY);
    double offsetX = (width - boxWidth * uniformScale) / 2;
    double offsetY = (height - boxHeight * uniformScale) / 2;
    
    Gdiplus::Matrix* matrix = new Gdiplus::Matrix;
    matrix->Scale(scale, scale);
    matrix->Translate(-boxOrigin.X, -boxOrigin.Y);
    matrix->Translate(offsetX / uniformScale, offsetY / uniformScale);
    matrix->Translate(-center.X, -center.Y);   
    matrix->Rotate(rotateAngle);          
    matrix->Translate(center.X, center.Y);    
    matrix->Scale(uniformScale, uniformScale);

    return matrix;
}