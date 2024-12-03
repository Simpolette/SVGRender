#include "PathRenderer.h"

PathRenderer::PathRenderer(const Fill& fill, const Stroke& stroke, const Transform& transform, const Path& path)
: Renderer(fill, stroke, transform){

}

void PathRenderer::render(Gdiplus::Graphics& graphics) const{

}