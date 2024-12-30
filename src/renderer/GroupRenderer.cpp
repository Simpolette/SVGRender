#include "GroupRenderer.h"
#include "RendererFactory.h"

GroupRenderer::GroupRenderer(const Fill& fill, const Stroke& stroke, const Transform& transform, RawElement* rawElement)
: Renderer(fill, stroke, transform){
    Group* group = dynamic_cast<Group*>(rawElement);
	const std::vector<RawElement*>& vec = group->getRawElement();
	for (int i = 0; i < vec.size(); i++) {
		Renderer* render = RendererFactory::createRenderer(vec[i]);
		if (render) {
			re.push_back(render); // Thêm Renderer tương ứng vào danh sách
		}
	}
}

void GroupRenderer::render(Gdiplus::Graphics& graphics) const {

    Gdiplus::Matrix originalMatrix;
    graphics.GetTransform(&originalMatrix);
    graphics.MultiplyTransform(matrix);


    
    // Duyệt qua tất cả các renderer và render chúng
    for (const Renderer* renderer : re) {
        if (renderer) { // Kiểm tra renderer không null
            renderer->render(graphics);
        }
    }

    // Reset transform sau khi vẽ xong nhóm
    graphics.SetTransform(&originalMatrix);
}