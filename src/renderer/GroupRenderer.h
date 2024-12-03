#ifndef _GROUP_RENDERER_H_
#define _GROUP_RENDERER_H_

#include "Renderer.h"

class GroupRenderer : public Renderer {

private:

public:
    GroupRenderer(const Fill& fill, const Stroke& stroke, const Transform& transform, const Group& group);
    void render(Gdiplus::Graphics& graphics) const override;
};

#endif