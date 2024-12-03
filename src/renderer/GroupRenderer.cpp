#include "GroupRenderer.h"

GroupRenderer::GroupRenderer(const Fill& fill, const Stroke& stroke, const Transform& transform, const Group& group)
: Renderer(fill, stroke, transform){

}

void GroupRenderer::render(Gdiplus::Graphics& graphics) const{

}