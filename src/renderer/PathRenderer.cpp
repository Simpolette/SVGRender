#include "PathRenderer.h"
#include <cmath>


const double PI = 3.14159265358979323846;  // Định nghĩa lại nếu chưa có
#define DEGREE (180 / PI)

float PathRenderer::CalculateVectorAngle(float x, float y) const {
    float angle = atan2(y, x);
    
    return angle * DEGREE;
}

PathRenderer::PathRenderer(const Fill& fill, const Stroke& stroke, const Transform& transform, RawElement* rawElement)
: Renderer(fill, stroke, transform) {
    Path* path = dynamic_cast<Path*>(rawElement);
    std::string fillRule = fill.getRule();
    if (fillRule == "evenodd"){
        pathGraphics.SetFillMode(Gdiplus::FillModeAlternate);
    }
    else if (fillRule == "nonzero"){
        pathGraphics.SetFillMode(Gdiplus::FillModeWinding);
    }

    const std::vector<std::pair<char, Gdiplus::PointF>>& pathData = path->getPath();

    Gdiplus::PointF startPoint(0, 0);
    Gdiplus::PointF currentPoint(0, 0);  // Điểm hiện tại (bắt đầu từ 0, 0) kiểu PointF
    pathGraphics.StartFigure();  // Bắt đầu một hình vẽ mới

    for (size_t i = 0; i < pathData.size(); ++i) {

        char command = pathData[i].first;
        Gdiplus::PointF point = pathData[i].second;

        switch (command) {
        case 'M':  // MoveTo (di chuyển đến vị trí mới)
            pathGraphics.StartFigure();  // Bắt đầu một hình vẽ mới
            currentPoint = point;  // Chuyển sang kiểu PointF
            startPoint = point;
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

        case 'S':  // Smooth cubic Bézier curve
            if (i + 1 < pathData.size()) {
                Gdiplus::PointF controlPoint1;

                if (i - 2 > 0 && (pathData[i - 2].first == 'C' || pathData[i - 2].first == 'S')) {
                    // Tính điểm đối xứng của điểm điều khiển trước đó
                    controlPoint1 = Gdiplus::PointF(
                        2 * currentPoint.X - pathData[i - 2].second.X, 
                        2 * currentPoint.Y - pathData[i - 2].second.Y
                    );

                } 
                else if (i - 2 > 0 && (pathData[i - 2].first == 'c' || pathData[i - 2].first == 's')){
                    Gdiplus::PointF absPreviousPoint = Gdiplus::PointF(currentPoint.X - pathData[i - 1].second.X + pathData[i - 2].second.X, currentPoint.Y - pathData[i - 1].second.Y + pathData[i - 2].second.Y);
                    controlPoint1 = Gdiplus::PointF(
                        2 * currentPoint.X - absPreviousPoint.X, 
                        2 * currentPoint.Y - absPreviousPoint.Y
                    );

                } else {
                    // Nếu không có lệnh Bézier trước đó, dùng currentPoint
                    controlPoint1 = currentPoint;
                }

                Gdiplus::PointF endPoint = pathData[i + 1].second;

                pathGraphics.AddBezier(currentPoint, controlPoint1, point, endPoint);
                currentPoint = endPoint;
                i += 1;
            }
            break;
        case 'Q':
            if (i + 1 < pathData.size()) {
                // startPoint = point, endPoint;
                Gdiplus::PointF endPoint = pathData[i + 1].second;

                // Sử dụng double cho các phép tính chính xác hơn
                double dx1 = point.X - currentPoint.X;
                double dy1 = point.Y - currentPoint.Y;
                Gdiplus::PointF ctrl1 = Gdiplus::PointF(
                    currentPoint.X + (2.0 / 3.0) * dx1,
                    currentPoint.Y + (2.0 / 3.0) * dy1
                );

                double dx2 = point.X - endPoint.X;
                double dy2 = point.Y - endPoint.Y;
                Gdiplus::PointF ctrl2 = Gdiplus::PointF(
                    endPoint.X + (2.0 / 3.0) * dx2,
                    endPoint.Y + (2.0 / 3.0) * dy2
                );

                // Chỉ làm tròn khi thực sự cần thiết (ví dụ, khi vẽ)
                pathGraphics.AddBezier(currentPoint, ctrl1, ctrl2, endPoint);

                currentPoint = endPoint;
                i += 1;
            }
            break;

        case 'T':  // Smooth cubic Bézier curve
            if (i < pathData.size()) {

                Gdiplus::PointF ctrl1;
                Gdiplus::PointF ctrl2;
                if (i - 1 > 0 && (pathData[i - 1].first == 'Q' || pathData[i - 1].first == 'T')) {
                    // Tính điểm đối xứng của điểm điều khiển trước đó
                    Gdiplus::PathData pathDataF;
                    pathGraphics.GetPathData(&pathDataF);
                    int size = pathDataF.Count;
                    Gdiplus::PointF prevCtrl1 = pathDataF.Points[size - 3];
                    Gdiplus::PointF prevCtrl2 = pathDataF.Points[size - 2];

                    ctrl1 = Gdiplus::PointF(
                        2 * currentPoint.X - prevCtrl1.X, 
                        2 * currentPoint.Y - prevCtrl1.Y
                    );

                    ctrl2 = Gdiplus::PointF(
                        2 * currentPoint.X - prevCtrl2.X, 
                        2 * currentPoint.Y - prevCtrl2.Y
                    );
                } 
                else if (i - 1 > 0 && (pathData[i - 1].first == 'q' || pathData[i - 1].first == 't')) {
                    // Tính điểm đối xứng của điểm điều khiển trước đó
                    Gdiplus::PathData pathDataF;
                    pathGraphics.GetPathData(&pathDataF);
                    int size = pathDataF.Count;
                    Gdiplus::PointF prevCtrl1 = pathDataF.Points[size - 3];
                    Gdiplus::PointF prevCtrl2 = pathDataF.Points[size - 2];

                    ctrl1 = Gdiplus::PointF(
                        2 * currentPoint.X - prevCtrl1.X, 
                        2 * currentPoint.Y - prevCtrl1.Y
                    );

                    ctrl2 = Gdiplus::PointF(
                        2 * currentPoint.X - prevCtrl2.X, 
                        2 * currentPoint.Y - prevCtrl2.Y
                    );
                } 

                else {
                    // Nếu không có lệnh Bézier trước đó, dùng currentPoint
                    ctrl1 = currentPoint;
                    ctrl2 = currentPoint;
                }

                Gdiplus::PointF endPoint = point;

                

                pathGraphics.AddBezier(currentPoint, ctrl2, ctrl1, endPoint);
                currentPoint = endPoint;

                
            }
            break;
        case 'A': {
            float cx,cy,cxp,cyp,theta1,dtheta;
            Gdiplus::GraphicsPath arc;
            Gdiplus::Matrix arc_mat;
            float rx = point.X;
            float ry = point.Y;

            float phi = pathData[i + 1].second.X;

            int fA = static_cast<int>(pathData[i + 2].second.X);
            int fS = static_cast<int>(pathData[i + 2].second.Y);

            // tim bounding rect
            Gdiplus::PointF p1 = currentPoint;
            Gdiplus::PointF p2 = pathData[i + 3].second;

            if (rx == 0 || ry == 0){
                pathGraphics.AddLine(p1, p2);
            }

            rx = abs(rx / DEGREE);
            ry = abs(ry / DEGREE);

            float x1 = p1.X;
            float y1 = p1.Y;
            float x2 = p2.X;
            float y2 = p2.Y;


            float cosPhi = cos(phi);
            float sinPhi = sin(phi);

            float x1p = (cosPhi * ((x1 - x2) / 2)) + (sinPhi * ((y1 - y2) / 2));
            float y1p = (-sinPhi * ((x1 - x2) / 2)) + (cosPhi * ((y1 - y2) / 2));

            float en = ((x1p*x1p)/(rx*rx)) + ((y1p*y1p)/(ry*ry));

            if (en > 1) {
                rx = sqrt(en) * rx;
                ry = sqrt(en) * ry;
                cx = (x1 + x2) / 2;
                cy = (y1 + y2) / 2;
                theta1 = CalculateVectorAngle(x1 - x2, y1 - y2) - phi;
                dtheta = 180;
            } else {
                en = sqrt(1 / en - 1);
                cxp = en * rx * y1p / ry;
                cyp = -en * ry * x1p / rx;
                if (fA == fS){
                    cxp = -cxp;
                    cyp = -cyp;
                }
                cx = (cosPhi*cxp - sinPhi*cyp) + ((x1 + x2) / 2);
                cy = (sinPhi*cxp + cosPhi*cyp) + ((y1 + y2) / 2);
                theta1 = CalculateVectorAngle(x1p - cxp, y1p - cyp);
                dtheta = CalculateVectorAngle(-x1p - cxp, -y1p - cyp) - theta1;
            }


            if(fS == 0 && dtheta > 0){
                dtheta -= 360;
            }else if(fS == 1 && dtheta < 0){
                dtheta += 360;
            }
            

            Gdiplus::PointF LRect(cx - rx, cy - ry);

            float width = 2 * rx;
            float height = 2 * ry;

            arc.AddArc(LRect.X, LRect.Y, width, height, theta1, dtheta);
            arc_mat.RotateAt(phi, Gdiplus::PointF(cx,cy));
            arc.Transform(&arc_mat);

            pathGraphics.AddPath(&arc, TRUE);

            currentPoint = p2;

            i += 3;
             
            break;
            }

        case 'Z':  // ClosePath (đóng đường vẽ)
            pathGraphics.CloseFigure();  // Đóng đường vẽ mà không cần AddLine
            break;

            // Các lệnh chữ thường:
        case 'm':  // moveTo (di chuyển đến vị trí mới theo tọa độ tương đối)
            pathGraphics.StartFigure();  // Bắt đầu một hình vẽ mới
            currentPoint.X += point.X;  // Di chuyển tương đối
            currentPoint.Y += point.Y;  // Di chuyển tương đối
            startPoint = currentPoint;
            break;
        case 'l':{  // lineTo (vẽ đường thẳng theo tọa độ tương đối)
            Gdiplus::PointF newP = Gdiplus::PointF(currentPoint.X + point.X, currentPoint.Y + point.Y);
            pathGraphics.AddLine(currentPoint, newP);
            currentPoint = newP;
            break;
        }
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

        case 'q':
            if (i + 1 < pathData.size()) {
                // startPoint = point, endPoint;
                Gdiplus::PointF endPoint = Gdiplus::PointF(currentPoint.X + pathData[i + 1].second.X, currentPoint.Y + pathData[i + 1].second.Y);
                point = Gdiplus::PointF(currentPoint.X + pathData[i].second.X, currentPoint.Y + pathData[i].second.Y);

                Gdiplus::PointF ctrl1 = Gdiplus::PointF(currentPoint.X + (2.0f / 3.0f) * (point.X - currentPoint.X),
                                                        currentPoint.Y + (2.0f / 3.0f) * (point.Y - currentPoint.Y));

                Gdiplus::PointF ctrl2 = Gdiplus::PointF(endPoint.X + (2.0f / 3.0f) * (point.X - endPoint.X),
                                                        endPoint.Y + (2.0f / 3.0f) * (point.Y - endPoint.Y));
                pathGraphics.AddBezier(currentPoint, ctrl1, ctrl2, endPoint);
                currentPoint = endPoint;
                i += 1;
            }
            break;
        case 's':  // Relative smooth cubic Bézier curve
            if (i + 1 < pathData.size()) {
                Gdiplus::PointF controlPoint1;

                if (i - 2 > 0 && (pathData[i - 2].first == 'C' || pathData[i - 2].first == 'S')) {

                    controlPoint1 = Gdiplus::PointF(
                        2 * currentPoint.X - pathData[i - 2].second.X,
                        2 * currentPoint.Y - pathData[i - 2].second.Y
                    );
                } else if (i - 2 > 0 && (pathData[i - 2].first == 'c' || pathData[i - 2].first == 's')) {

                    Gdiplus::PointF absPreviousPoint = Gdiplus::PointF(
                        currentPoint.X - pathData[i - 1].second.X + pathData[i - 2].second.X,
                        currentPoint.Y - pathData[i - 1].second.Y + pathData[i - 2].second.Y
                    );

                    controlPoint1 = Gdiplus::PointF(
                        2 * currentPoint.X - absPreviousPoint.X,
                        2 * currentPoint.Y - absPreviousPoint.Y
                    );
                } else {

                    controlPoint1 = currentPoint;
                }

                Gdiplus::PointF controlPoint2 = Gdiplus::PointF(
                    currentPoint.X + pathData[i].second.X,
                    currentPoint.Y + pathData[i].second.Y
                );

                Gdiplus::PointF endPoint = Gdiplus::PointF(
                    currentPoint.X + pathData[i + 1].second.X,
                    currentPoint.Y + pathData[i + 1].second.Y
                );

                pathGraphics.AddBezier(currentPoint, controlPoint1, controlPoint2, endPoint);

                currentPoint = endPoint;

                i += 1;
            }
            break;
        case 't':  // Smooth cubic Bézier curve (relative)
            if (i < pathData.size()) {

                Gdiplus::PointF ctrl1;
                Gdiplus::PointF ctrl2;

                if (i - 1 > 0 && (pathData[i - 1].first == 'q' || pathData[i - 1].first == 't')) {
                    // Tính điểm đối xứng của điểm điều khiển trước đó (relative coordinates)
                    Gdiplus::PathData pathData;
                    pathGraphics.GetPathData(&pathData);
                    int size = pathData.Count;
                    Gdiplus::PointF prevCtrl1 = pathData.Points[size - 3];
                    Gdiplus::PointF prevCtrl2 = pathData.Points[size - 2];

                    // Sử dụng relative coordinates so với currentPoint
                    ctrl1 = Gdiplus::PointF(
                        2 * currentPoint.X - prevCtrl1.X, 
                        2 * currentPoint.Y - prevCtrl1.Y
                    );

                    ctrl2 = Gdiplus::PointF(
                        2 * currentPoint.X - prevCtrl2.X, 
                        2 * currentPoint.Y - prevCtrl2.Y
                    );
                } 
                else {
                    // Nếu không có lệnh Bézier trước đó, dùng currentPoint cho các điều khiển
                    ctrl1 = currentPoint;
                    ctrl2 = currentPoint;
                }

                Gdiplus::PointF endPoint = point; // Điểm kết thúc (tương đối với currentPoint)

                // Thêm lệnh Bézier cubic vào đồ họa (relative)
                pathGraphics.AddBezier(currentPoint, ctrl2, ctrl1, endPoint);
                currentPoint = endPoint;
            }
            break;


        case 'a':{
           
                Gdiplus::GraphicsPath arc;
                Gdiplus::Matrix arc_mat;
                float cx,cy,cxp,cyp,theta1,dtheta;

                float rx = point.X;
                float ry = point.Y;

                float phi = pathData[i + 1].second.X + 1;

                int fA = pathData[i + 2].second.X;
                int fS = pathData[i + 2].second.Y;

                // tim bounding rect
                Gdiplus::PointF p1 = currentPoint;
                Gdiplus::PointF p2 = Gdiplus::PointF(pathData[i + 3].second.X + currentPoint.X, pathData[i + 3].second.Y + currentPoint.Y);


                if (rx == 0 || ry == 0){
                    pathGraphics.AddLine(p1, p2);
                }

                rx = abs(rx);
                ry = abs(ry);

                float x1 = p1.X;
                float y1 = p1.Y;
                float x2 = p2.X;
                float y2 = p2.Y;


                float cosPhi = cos(phi / DEGREE);
                float sinPhi = sin(phi / DEGREE);

                float x1p = (cosPhi * ((x1 - x2) / 2)) + (sinPhi * ((y1 - y2) / 2));
                float y1p = (-sinPhi * ((x1 - x2) / 2)) + (cosPhi * ((y1 - y2) / 2));

                float en = ((x1p*x1p)/(rx*rx)) + ((y1p*y1p)/(ry*ry));

                if (en > 1) {
                    rx *= sqrt(en);
                    ry *= sqrt(en);
                    cx = (x1 + x2) / 2;
                    cy = (y1 + y2) / 2;
                    theta1 = CalculateVectorAngle(x1 - x2, y1 - y2) - phi;
                    dtheta = 180.0;
                } else {
                    en = sqrt(1 / en - 1);
                    cxp = en * rx * y1p / ry;
                    cyp = -en * ry * x1p / rx;
                    if (fA == fS){
                        cxp = -cxp;
                        cyp = -cyp;
                    }
                    cx = (cosPhi*cxp - sinPhi*cyp) + ((x1 + x2) / 2);
                    cy = (sinPhi*cxp + cosPhi*cyp) + ((y1 + y2) / 2);
                    theta1 = CalculateVectorAngle(x1p - cxp, y1p - cyp);
                    dtheta = CalculateVectorAngle(-x1p - cxp, -y1p - cyp) - theta1;
                }


                if(fS == 0 && dtheta > 0){
                    dtheta -= 360.000001;
                }else if(fS == 1 && dtheta < 0){
                    dtheta += 360.000001;
                }
                


                float width = 2 * rx;
                float height = 2 * ry;



                arc.AddArc(cx - rx, cy - ry, 2 * rx, 2 * ry, theta1, dtheta);
                arc_mat.RotateAt(phi, Gdiplus::PointF(cx,cy));
                arc.Transform(&arc_mat);

                pathGraphics.AddPath(&arc, TRUE);

                currentPoint = p2;

                i += 3;
            
            break;
            }
        case 'z':  // closePath (đóng đường vẽ)
            pathGraphics.CloseFigure();
            currentPoint = startPoint;
            break;

        default:
            break;
        }
    }

    Gdiplus::RectF bound;
    pathGraphics.GetBounds(&bound);
    if (!brush){
        brush = fill.getGradientBrush(bound);
    }
}

void PathRenderer::render(Gdiplus::Graphics& graphics) const {
    Gdiplus::Matrix originalMatrix;
    graphics.GetTransform(&originalMatrix);
    graphics.MultiplyTransform(matrix);

    // Vẽ hình theo đường path đã tạo ra
    graphics.FillPath(brush, &pathGraphics);  // Tô màu path
    graphics.DrawPath(pen, &pathGraphics);    // Vẽ đường viền path

    graphics.SetTransform(&originalMatrix);
}
