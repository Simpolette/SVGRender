#include "PathRenderer.h"

PathRenderer::PathRenderer(const Fill& fill, const Stroke& stroke, const Transform& transform, const Path& path)
    : Renderer(fill, stroke, transform), path(path) {}

void PathRenderer::render(Gdiplus::Graphics& graphics) const {
    Gdiplus::Matrix originalMatrix;
    graphics.GetTransform(&originalMatrix);
    graphics.MultiplyTransform(matrix);

    Gdiplus::GraphicsPath pathGraphics;
    const std::vector<std::pair<char, Gdiplus::PointF>>& pathData = path.getPath();

    Gdiplus::PointF currentPoint(0, 0);  // Điểm hiện tại (bắt đầu từ 0, 0) kiểu PointF
    pathGraphics.StartFigure();  // Bắt đầu một hình vẽ mới

    for (size_t i = 0; i < pathData.size(); ++i) {
        char command = pathData[i].first;
        Gdiplus::PointF point = pathData[i].second;

        switch (command) {
        case 'M':  // MoveTo (di chuyển đến vị trí mới)
            pathGraphics.CloseFigure();
            pathGraphics.StartFigure();  // Bắt đầu một hình vẽ mới
            currentPoint = point;  // Chuyển sang kiểu PointF
            break;
        case 'L':  // LineTo (vẽ đường thẳng)
            pathGraphics.AddLine(currentPoint, point);  // Sử dụng PointF thay vì PointF
            currentPoint = point;  // Cập nhật currentPoint
            break;
        case 'H':  // Horizontal LineTo (vẽ đường ngang)
            pathGraphics.AddLine(currentPoint, Gdiplus::PointF(point.X, currentPoint.Y));  // Sử dụng PointF
            currentPoint.X = point.X;  // Chỉ thay đổi X, Y giữ nguyên
            break;
        case 'V':  // Vertical LineTo (vẽ đường dọc)
            pathGraphics.AddLine(currentPoint, Gdiplus::PointF(currentPoint.X, point.Y));  // Sử dụng PointF
            currentPoint.Y = point.Y;  // Chỉ thay đổi Y, X giữ nguyên
            break;
        case 'C':  // Cubic Bezier Curve (đường cong Bezier bậc 3)
            if (i + 2 < pathData.size()) {  // Kiểm tra xem có đủ điểm điều khiển không
                Gdiplus::PointF controlPoint1 = pathData[i + 1].second;
                Gdiplus::PointF controlPoint2 = pathData[i + 2].second;

                // Vẽ đường cong Bezier bậc 3
                pathGraphics.AddBezier(currentPoint, point, controlPoint1, controlPoint2);  // Sử dụng PointF
                currentPoint = controlPoint2;  // Cập nhật currentPoint là điểm kết thúc của đường cong Bezier
                i += 2;  // Di chuyển chỉ số tới điểm tiếp theo sau ba điểm điều khiển
            }
            break;
        case 'Z':  // ClosePath (đóng đường vẽ)
            pathGraphics.CloseFigure();  // Đóng đường vẽ mà không cần AddLine
            break;

            // Các lệnh chữ thường:
        case 'm':  // moveTo (di chuyển đến vị trí mới theo tọa độ tương đối)
            pathGraphics.CloseFigure();
            pathGraphics.StartFigure();  // Bắt đầu một hình vẽ mới
            currentPoint.X += point.X;  // Di chuyển tương đối
            currentPoint.Y += point.Y;  // Di chuyển tương đối
            break;
        case 'l':  // lineTo (vẽ đường thẳng theo tọa độ tương đối)
            pathGraphics.AddLine(currentPoint, Gdiplus::PointF(currentPoint.X + point.X, currentPoint.Y + point.Y));
            currentPoint.X += point.X;  // Cập nhật tọa độ hiện tại theo tọa độ tương đối
            currentPoint.Y += point.Y;
            break;
        case 'h':  // horizontal lineTo (vẽ đường ngang theo tọa độ tương đối)
            pathGraphics.AddLine(currentPoint, Gdiplus::PointF(currentPoint.X + point.X, currentPoint.Y));
            currentPoint.X += point.X;  // Chỉ thay đổi X, Y giữ nguyên
            break;
        case 'v':  // vertical lineTo (vẽ đường dọc theo tọa độ tương đối)
            pathGraphics.AddLine(currentPoint, Gdiplus::PointF(currentPoint.X, currentPoint.Y + point.Y));
            currentPoint.Y += point.Y;  // Chỉ thay đổi Y, X giữ nguyên
            break;
        case 'c':  // cubic Bezier curve (đường cong Bezier bậc 3 theo tọa độ tương đối)
            if (i + 2 < pathData.size()) {  // Kiểm tra xem có đủ điểm điều khiển không
                Gdiplus::PointF controlPoint1 = Gdiplus::PointF(currentPoint.X + pathData[i + 1].second.X, currentPoint.Y + pathData[i + 1].second.Y);
                Gdiplus::PointF controlPoint2 = Gdiplus::PointF(currentPoint.X + pathData[i + 2].second.X, currentPoint.Y + pathData[i + 2].second.Y);

                // Vẽ đường cong Bezier bậc 3
                pathGraphics.AddBezier(currentPoint, Gdiplus::PointF(currentPoint.X + point.X, currentPoint.Y + point.Y), controlPoint1, controlPoint2);
                currentPoint = controlPoint2;  // Cập nhật currentPoint là điểm kết thúc của đường cong Bezier
                i += 2;  // Di chuyển chỉ số tới điểm tiếp theo sau ba điểm điều khiển
            }
            break;
        case 's':  // smooth cubic Bezier curve (đường cong Bezier bậc 3 mượt mà theo tọa độ tương đối)
            // Implement tương tự như đường cong Bezier bậc 3, nhưng với điều kiện mượt mà
            break;
        case 'z':  // closePath (đóng đường vẽ)
            pathGraphics.CloseFigure();
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
