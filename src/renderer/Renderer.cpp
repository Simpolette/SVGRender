#include "Renderer.h"

Renderer::Renderer(const Fill& fill, const Stroke& stroke, const Transform& transform){
    pen = stroke.getPen();
    brush = fill.getBrush();
    matrix = transform.getMatrix();
}

Renderer::~Renderer(){
    delete pen;
    delete brush;
    delete matrix;
}