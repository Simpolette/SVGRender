#ifndef _VIEWER_H_
#define _VIEWER_H_

#include <vector>
#include "../renderer/Renderer.h"

class Viewer{

private:
    double scale;
    double rotateAngle;
    double width;
    double height;
    Gdiplus::PointF center;

    double boxWidth;
    double boxHeight;
    Gdiplus::PointF boxOrigin;

    std::vector <Renderer*> elements;

public:
    Viewer();
    ~Viewer();
    void addRenderer(Renderer* renderer);
    void render(Gdiplus::Graphics& graphics);
    void setCenter(Gdiplus::PointF center);
    void setBoxWidth(double boxWidth);
    void setBoxHeight(double boxHeight);
    void setBoxOrigin(Gdiplus::PointF boxOrigin);
    void setViewPort(HDC hdc);
    void zoom(int delta);
    void rotateLeft();
    void rotateRight();
    Gdiplus::Matrix* getViewBoxMatrix();
};

#endif