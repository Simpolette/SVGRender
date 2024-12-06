#include "PathRenderer.h"

PathRenderer::PathRenderer(const Fill& fill, const Stroke& stroke, const Transform& transform, const Path& path)
    : Renderer(fill, stroke, transform), path(path) {}

void PathRenderer::render(Gdiplus::Graphics& graphics) const {
    Gdiplus::Matrix originalMatrix;
    graphics.GetTransform(&originalMatrix);
    graphics.MultiplyTransform(matrix);



    
    Gdiplus::GraphicsPath pathGraphics;
    const std::vector<std::pair<char, Gdiplus::Point>>& pathData = path.getPath();

    Gdiplus::Point currentPoint(0, 0);  // Điểm hiện tại (bắt đầu từ 0, 0) kiểu Point
    pathGraphics.StartFigure();  // Bắt đầu một hình vẽ mới

    for (size_t i = 0; i < pathData.size(); ++i) {
        char command = pathData[i].first;
        Gdiplus::Point point = pathData[i].second;

        switch (command) {
        case 'M':  // MoveTo (di chuyển đến vị trí mới)
            currentPoint = point;  // Chuyển sang kiểu Point
            break;
        case 'L':  // LineTo (vẽ đường thẳng)
            pathGraphics.AddLine(currentPoint, point);  // Sử dụng Point thay vì PointF
            currentPoint = point;  // Cập nhật currentPoint
            break;
        case 'H':  // Horizontal LineTo (vẽ đường ngang)
            pathGraphics.AddLine(currentPoint, Gdiplus::Point(point.X, currentPoint.Y));  // Sử dụng Point
            currentPoint.X = point.X;  // Chỉ thay đổi X, Y giữ nguyên
            break;
        case 'V':  // Vertical LineTo (vẽ đường dọc)
            pathGraphics.AddLine(currentPoint, Gdiplus::Point(currentPoint.X, point.Y));  // Sử dụng Point
            currentPoint.Y = point.Y;  // Chỉ thay đổi Y, X giữ nguyên
            break;
        case 'C':  // Cubic Bezier Curve (đường cong Bezier bậc 3)
            if (i + 2 < pathData.size()) {  // Kiểm tra xem có đủ điểm điều khiển không
                Gdiplus::Point controlPoint1 = pathData[i + 1].second;
                Gdiplus::Point controlPoint2 = pathData[i + 2].second;

                // Vẽ đường cong Bezier bậc 3
                pathGraphics.AddBezier(currentPoint, point, controlPoint1, controlPoint2);  // Sử dụng Point
                currentPoint = controlPoint2;  // Cập nhật currentPoint là điểm kết thúc của đường cong Bezier
                i += 2;  // Di chuyển chỉ số tới điểm tiếp theo sau ba điểm điều khiển
            }
            break;
        case 'Z':  // ClosePath (đóng đường vẽ)
            pathGraphics.CloseFigure();  // Đóng đường vẽ mà không cần AddLine
            break;
        default:
            break;
        }
    }

    // Vẽ hình theo đường path đã tạo ra
    graphics.FillPath(brush, &pathGraphics);  // Tô màu path
    graphics.DrawPath(pen, &pathGraphics);    // Vẽ đường viền path

    graphics.SetTransform(&originalMatrix);
}