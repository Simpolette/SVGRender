// #include "stdafx.h"
#include <vector>
#include <fstream>

#include "renderer/RendererFactory.h"
#include "file_reader/SVG.h"
#include "viewer/Viewer.h"

#pragma comment (lib,"Gdiplus.lib")

Viewer viewer;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

VOID OnPaint(HDC hdc){
   Gdiplus::Graphics graphics(hdc);
   graphics.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);
   
   Gdiplus::Matrix matrix;
   matrix.Scale(scale, scale); 

   RECT clientRect;
   GetClientRect(WindowFromDC(hdc), &clientRect);
   float centerX = (clientRect.right - clientRect.left);
   float centerY = (clientRect.bottom - clientRect.top);

   GetSVG getSVG;
   vec = getSVG.parseSVGFile(filePath);
   int n = vec.size();

   double viewWidth = getSVG.getViewWidth();
   double viewHeight = getSVG.getViewHeight();
   Gdiplus::PointF boxOrigin = getSVG.getBoxOrigin();
   double boxWidth = getSVG.getBoxWidth();
   double boxHeight = getSVG.getBoxHeight();
      // Áp dụng các phép biến đổi
   matrix.Translate(-centerX, -centerY);  // Dịch về gốc tọa độ

   matrix.Rotate(rotationAngle);         // Xoay quanh gốc
   matrix.Translate(centerX, centerY);   // Dịch về vị trí ban đầu
   matrix.Scale(scale, scale);           // Áp dụng zoom
   graphics.SetTransform(&matrix);


   for (int i = 0; i < n; i++){
      // vec[i]->print();
      Renderer* render = RendererFactory::createRenderer(vec[i]);
      render->render(graphics);
      
      delete vec[i];
      delete render; 
   }
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow)
{
   // AllocConsole();
   // freopen("CONOUT$", "w", stdout);
   HWND                          hWnd;
   MSG                           msg;
   WNDCLASS                      wndClass;
   Gdiplus::GdiplusStartupInput  gdiplusStartupInput;
   ULONG_PTR                     gdiplusToken;
   
   // Initialize GDI+.
   Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
   
   wndClass.style          = CS_HREDRAW | CS_VREDRAW;
   wndClass.lpfnWndProc    = WndProc;
   wndClass.cbClsExtra     = 0;
   wndClass.cbWndExtra     = 0;
   wndClass.hInstance      = hInstance;
   wndClass.hIcon          = LoadIcon(NULL, IDI_APPLICATION);
   wndClass.hCursor        = LoadCursor(NULL, IDC_ARROW);
   wndClass.hbrBackground  = (HBRUSH)GetStockObject(WHITE_BRUSH);
   wndClass.lpszMenuName   = NULL;
   wndClass.lpszClassName  = TEXT("GettingStarted");
   
   RegisterClass(&wndClass);
   
   hWnd = CreateWindow(
      TEXT("GettingStarted"),   // window class name
      TEXT("SVG Demo"),  // window caption
      WS_OVERLAPPEDWINDOW,      // window style
      CW_USEDEFAULT,            // initial x position
      CW_USEDEFAULT,            // initial y position
      CW_USEDEFAULT,            // initial x size
      CW_USEDEFAULT,            // initial y size
      NULL,                     // parent window handle
      NULL,                     // window menu handle
      hInstance,                // program instance handle
      NULL);                    // creation parameters
      
   ShowWindow(hWnd, iCmdShow);
   UpdateWindow(hWnd);
   
   GetSVG getSVG;
   if (argument && argument[0]){
      std::string filePath = argument;
      std::vector<RawElement*> vec;
      vec = getSVG.parseSVGFile(filePath);
      viewer.setBoxOrigin(getSVG.getBoxOrigin());
      viewer.setBoxWidth(getSVG.getBoxWidth());
      viewer.setBoxHeight(getSVG.getBoxHeight());

      for (int i = 0; i < vec.size(); i++){
         // vec[i]->print();
         Renderer* render = RendererFactory::createRenderer(vec[i]);
         viewer.addRenderer(render);
         
         delete vec[i];
      }
   }

   while(GetMessage(&msg, NULL, 0, 0))
   {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
   }
   
   // FreeConsole();
   Gdiplus::GdiplusShutdown(gdiplusToken);
   return msg.wParam;
}  // WinMain

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, 
   WPARAM wParam, LPARAM lParam)
{
   HDC          hdc;
   PAINTSTRUCT  ps;

   switch(message)
   {
   case WM_PAINT:{
      hdc = BeginPaint(hWnd, &ps);
      OnPaint(hdc);

      EndPaint(hWnd, &ps);
      return 0;
   }
   case WM_MOUSEWHEEL: {
       int zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
       viewer.zoom(zDelta);
       InvalidateRect(hWnd, NULL, TRUE);
       return 0;
   }
   case WM_KEYDOWN:
       switch (wParam) {
       case VK_LEFT: // Xoay ngược chiều kim đồng hồ
            viewer.rotateLeft();
            InvalidateRect(hWnd, NULL, TRUE);
            break;
       case VK_RIGHT: // Xoay thuận chiều kim đồng hồ
            viewer.rotateRight();
            InvalidateRect(hWnd, NULL, TRUE);
            break;
       case VK_UP: // Zoom in
            viewer.zoom(1);
            InvalidateRect(hWnd, NULL, TRUE);
            break;
       case VK_DOWN: // Zoom out
            viewer.zoom(-1);
            InvalidateRect(hWnd, NULL, TRUE);
            break;
       }
       return 0;
   case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
   default:
      return DefWindowProc(hWnd, message, wParam, lParam);
   }
} // WndProc
