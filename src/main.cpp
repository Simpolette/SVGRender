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
   viewer.setViewPort(hdc);
   Gdiplus::Matrix* viewBoxMatrix = viewer.getViewBoxMatrix();
   graphics.SetTransform(viewBoxMatrix);
   viewer.render(graphics);
}

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR argument, INT iCmdShow)
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
