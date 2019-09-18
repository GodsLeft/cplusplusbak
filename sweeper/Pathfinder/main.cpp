#include <windows.h>
#include <time.h>

#include "defines.h"
#include "utils.h"
#include "CgaBob.h"

#pragma comment(lib, "winmm")

char* g_szApplicationName = "Hello World3 Ball";
char* g_szWindowClassName = "MyWindowClass";

CgaBob* g_pGABob;

LRESULT CALLBACK WindowProc(HWND	hwnd,
							UINT	msg,
							WPARAM	wParam,
							LPARAM	lParam)
{
	HDC				hdc;
	PAINTSTRUCT		ps;
	static int cxClient, cyClient;
	
	static HDC		hdcBackBuffer;
	static HBITMAP	hBitmap;
	static HBITMAP	hOldBitmap;

	switch(msg)
	{
	case WM_CREATE:
		{
			srand((unsigned) time(NULL));
			g_pGABob = new CgaBob(CROSSOVER_RATE,
									MUTATION_RATE,
									POP_SIZE,
									CHROMO_LENGTH,
									GENE_LENGTH);
			RECT rect;
			GetClientRect(hwnd, &rect);
			cxClient = rect.right;
			cyClient = rect.bottom;

			hdcBackBuffer = CreateCompatibleDC(NULL);
			HDC hdc = GetDC(hwnd);
			hBitmap = CreateCompatibleBitmap(hdc, cxClient, cyClient);

			ReleaseDC(hwnd, hdc);
			hOldBitmap = (HBITMAP)SelectObject(hdcBackBuffer, hBitmap);

		}
		break;
	
	case WM_PAINT:
		{
			hdc = BeginPaint(hwnd, &ps);

			BitBlt(hdcBackBuffer, 0, 0, cxClient, cyClient, NULL, NULL, NULL, WHITENESS);
			g_pGABob->Render(cxClient, cyClient, hdcBackBuffer);
			BitBlt(hdc, 0, 0, cxClient, cyClient, hdcBackBuffer, 0, 0, SRCCOPY);
			ReleaseDC(hwnd, hdc);
			EndPaint(hwnd, &ps);
		}
		break;

	case WM_KEYUP:
		{
			switch(wParam){
			case VK_RETURN:{
				g_pGABob->Run(hwnd);
			}
				break;

			case VK_SPACE:{
				g_pGABob->Stop();
			}
				break;
			case VK_ESCAPE:{
					PostQuitMessage(0);		   
				}
				break;
			}
		}
		break;

	case WM_DESTROY:
		{
			SelectObject(hdcBackBuffer, hOldBitmap);
			DeleteDC(hdcBackBuffer);
			DeleteObject(hBitmap);
			delete g_pGABob;

			PostQuitMessage(0);
		}
		break;

	case WM_SIZE:
		{
			cxClient = LOWORD(lParam);
			cyClient = HIWORD(lParam);

			//当窗口大小改变的时候，重新设置缓冲
			SelectObject(hdcBackBuffer, hOldBitmap);
			//DeleteObject(hBitmap);
			HDC hdc = GetDC(hwnd);
			hBitmap = CreateCompatibleBitmap(hdc, cxClient, cyClient);
			ReleaseDC(hwnd, hdc);
			hOldBitmap = (HBITMAP)SelectObject(hdcBackBuffer, hBitmap);
			//SelectObject(hdcBackBuffer, hBitmap);
		}
		break;
	default:break;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}



int WINAPI WinMain(HINSTANCE	hInstance,
					HINSTANCE	hPrevInstance,
					LPSTR		szCmdLine,
					int			iCmdShow)
{
	HWND	hWnd;
	WNDCLASSEX		winclass;
	winclass.cbSize		= sizeof(WNDCLASSEX);
	winclass.style		= CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc	= WindowProc;
	winclass.cbClsExtra		= 0;
	winclass.cbWndExtra		= 0;
	winclass.hInstance		= hInstance;
	winclass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor		= LoadCursor(NULL, IDC_ARROW);
	//winclass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	winclass.hbrBackground	= NULL;
	winclass.lpszMenuName	= NULL;
	winclass.lpszClassName	= g_szWindowClassName;
	winclass.hIconSm		= LoadIcon(NULL, IDI_APPLICATION);

	if(!RegisterClassEx(&winclass))
	{
		MessageBoxA(NULL, "Class Registration Failed!", "Error", 0);
		return 0;
	}

	hWnd = CreateWindowEx(NULL,
							g_szWindowClassName,
							g_szApplicationName,
							WS_OVERLAPPEDWINDOW,
							0,
							0,
							WINDOW_WIDTH,
							WINDOW_HEIGHT,
							NULL,
							NULL,
							hInstance,
							NULL);
	if(!hWnd){
		MessageBoxA(NULL, "CreateWindowEx Failed!", "Error!", 0);
	}

	ShowWindow(hWnd, iCmdShow);
	UpdateWindow(hWnd);

	bool bDone = false;
	MSG msg;

	//游戏主循环
	while(!bDone){
		while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
			if(msg.message == WM_QUIT){
				bDone = true;
			}else{			
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		if(g_pGABob->Started()){
			g_pGABob->Epoch();
			InvalidateRect(hWnd, NULL, TRUE);
			UpdateWindow(hWnd);
		}
		
	}

	UnregisterClass(g_szApplicationName, winclass.hInstance);

	return 0;
	//return msg.wParam;
}