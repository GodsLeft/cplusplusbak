#include <windows.h>
#include <time.h>

#include "defines.h"
#include "utils.h"
#include "CTimer.h"

#pragma comment(lib, "winmm")

char* g_szApplicationName = "Hello World3 Ball";
char* g_szWindowClassName = "MyWindowClass";

struct SBall{
	int posX;
	int posY;
	int velX;
	int velY;
	SBall(){}
};

LRESULT CALLBACK WindowProc(HWND	hwnd,
							UINT	msg,
							WPARAM	wParam,
							LPARAM	lParam)
{
	static int cxClient, cyClient;
	static HPEN BluePen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	static HPEN OldPen = NULL;

	static HBRUSH RedBrush = CreateSolidBrush(RGB(255, 0, 0));
	static HBRUSH OldBrush = NULL;

	static SBall* balls = new SBall[NUM_BALLS];

	static HDC		hdcBackBuffer;
	static HBITMAP	hBitmap;
	static HBITMAP	hOldBitmap;

	switch(msg)
	{
	case WM_CREATE:
		{
			//PlaySound("window_open.wav", NULL, SND_FILENAME | SND_ASYNC);
			RECT rect;
			GetClientRect(hwnd, &rect);
			cxClient = rect.right;
			cyClient = rect.bottom;

			srand((unsigned)time(NULL));
			for(int i=0; i<NUM_BALLS; ++i){
				balls[i].posX = RandInt(0, cxClient);
				balls[i].posY = RandInt(0, cyClient);
				balls[i].velX = RandInt(0, MAX_VELOCITY);
				balls[i].velY = RandInt(0, MAX_VELOCITY);
			}

			hdcBackBuffer	= CreateCompatibleDC(NULL);
			HDC hdc		= GetDC(hwnd);
			hBitmap		= CreateCompatibleBitmap(hdc, cxClient, cyClient);
			hOldBitmap	= (HBITMAP)SelectObject(hdcBackBuffer, hBitmap);
			ReleaseDC(hwnd, hdc);
		}
		break;
	
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			BeginPaint(hwnd, &ps);

			BitBlt(hdcBackBuffer, 0, 0, cxClient, cyClient, NULL, NULL, NULL, WHITENESS);
			OldPen = (HPEN)SelectObject(hdcBackBuffer, BluePen);
			OldBrush = (HBRUSH)SelectObject(hdcBackBuffer, RedBrush);

			for(int i=0; i<NUM_BALLS; ++i){
				if((balls[i].posX >= cxClient) || (balls[i].posX <0)){
					balls[i].velX = -balls[i].velX;
				}
				if((balls[i].posY >= cyClient) || (balls[i].posY <0)){
					balls[i].velY = -balls[i].velY;
				}

				balls[i].posX += balls[i].velX;
				balls[i].posY += balls[i].velY;

				Ellipse(hdcBackBuffer,
						balls[i].posX - RADIUS,
						balls[i].posY - RADIUS,
						balls[i].posX + RADIUS,
						balls[i].posY + RADIUS);
			}
			
			SelectObject(hdcBackBuffer, OldPen);
			SelectObject(hdcBackBuffer, OldBrush);
			BitBlt(ps.hdc, 0, 0, cxClient, cyClient, hdcBackBuffer, 0, 0, SRCCOPY);
			EndPaint(hwnd, &ps);
			Sleep(10);
		}
		break;

	case WM_KEYUP:
		{
			switch(wParam){
			case VK_ESCAPE:{
					PostQuitMessage(0);		   
				}
				break;
			}
		}
		break;

	case WM_DESTROY:
		{
			DeleteObject(BluePen);
			DeleteObject(OldPen);
			DeleteObject(RedBrush);
			DeleteObject(OldBrush);

			delete[] balls;
			SelectObject(hdcBackBuffer, hOldBitmap);
			DeleteDC(hdcBackBuffer);
			DeleteObject(hBitmap);

			PostQuitMessage(0);
		}
		break;

	case WM_SIZE:
		{
			cxClient = LOWORD(lParam);
			cyClient = HIWORD(lParam);

			//当窗口大小改变的时候，重新设置缓冲
			SelectObject(hdcBackBuffer, hOldBitmap);
			DeleteObject(hBitmap);
			HDC hdc = GetDC(hwnd);
			hBitmap = CreateCompatibleBitmap(hdc, cxClient, cyClient);
			ReleaseDC(hwnd, hdc);
			SelectObject(hdcBackBuffer, hBitmap);
		}
		break;
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
	CTimer	timer(FRAMES_PER_SECOND);
	timer.Start();
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

		if(timer.ReadyForNextFrame()){
			InvalidateRect(hWnd, NULL, TRUE);
			UpdateWindow(hWnd);
		}
		
	}

	UnregisterClass(g_szApplicationName, winclass.hInstance);

	return msg.wParam;
}