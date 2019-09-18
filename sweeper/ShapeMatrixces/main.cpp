#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <mmsystem.h>

#include "defines.h"
#include "utils.h"
#include "CTimer.h"
#include "CGun.h"

char*	szApplicationName = "Transformations with Matrix";
char*	szWindowClassName = "Simple shapes";

CGun g_Gun(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 5, 0);

LRESULT	CALLBACK WindowProc(HWND	hWnd,
							UINT	msg,
							WPARAM	wparam,
							LPARAM	lparam)
{
	static int cxClient, cyClient;
	static HDC		hdcBackBuffer;
	static HBITMAP	hBitmap;
	static HBITMAP	hOldBitmap;

	switch(msg)
	{
	case WM_CREATE:
		{
			srand((unsigned) time(NULL));
			RECT rect;
			GetClientRect(hWnd, &rect);
			cxClient = rect.right;
			cyClient = rect.bottom;

			hdcBackBuffer = CreateCompatibleDC(NULL);
			HDC hdc = GetDC(hWnd);
			hBitmap = CreateCompatibleBitmap(hdc, cxClient, cyClient);
			ReleaseDC(hWnd, hdc);
			hOldBitmap = (HBITMAP)SelectObject(hdcBackBuffer, hBitmap);
		}
		break;

	case WM_KEYUP:
		{
			switch(wparam){
			case VK_ESCAPE:{
				PostQuitMessage(0);
						   }
						   break;
			}
		}
		break;

	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			BeginPaint(hWnd, &ps);
			BitBlt(hdcBackBuffer, 0, 0, cxClient, cyClient, NULL, NULL, NULL, WHITENESS);
			g_Gun.Render(hdcBackBuffer);
			BitBlt(ps.hdc, 0, 0, cxClient, cyClient, hdcBackBuffer, 0, 0, SRCCOPY);
			EndPaint(hWnd, &ps);
		}
		break;

	case WM_DESTROY:
		{
			SelectObject(hdcBackBuffer, hOldBitmap);
			DeleteDC(hdcBackBuffer);
			DeleteObject(hBitmap);
			PostQuitMessage(0);
		}
		break;

	default:break;
	}
	return (DefWindowProc(hWnd, msg, wparam, lparam));
}

int WINAPI WinMain(HINSTANCE	hinstance,
					HINSTANCE	hprevinstance,
					LPSTR		lpcmdline,
					int			ncmdshow)
{
	WNDCLASSEX	winclass;
	HWND		hWnd;
	MSG			msg;

	winclass.cbSize			= sizeof(WNDCLASSEX);
	winclass.style			= CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc	= WindowProc;
	winclass.cbClsExtra		= 0;
	winclass.cbWndExtra		= 0;
	winclass.hInstance		= hinstance;
	winclass.hIcon			= NULL;
	winclass.hCursor		= LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground	= NULL;
	winclass.lpszMenuName	= NULL;
	winclass.lpszClassName	= szWindowClassName;
	winclass.hIconSm		= NULL;
	//winclass.hIconSm		= LoadIcon(NULL, IDI_APPLICATION);

	if(!RegisterClassEx(&winclass))
	{
		MessageBox(NULL, "Error Registering Class!", "Error", 0);
		return 0;
	}

	if(!(hWnd = CreateWindowEx(NULL,
								szWindowClassName,
								szApplicationName,
								WS_OVERLAPPED | WS_VISIBLE | WS_CAPTION | WS_SYSMENU,
								0, 0,
								WINDOW_WIDTH, WINDOW_HEIGHT,
								NULL,
								NULL,
								hinstance,
								NULL)))
	{
		MessageBox(NULL,"Error Creating Window!", "Error", 0);
		return 0;
	}

	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);

	CTimer timer(FRAMES_PER_SECOND);
	timer.Start();

	bool bDone = false;
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
			g_Gun.Update();
			InvalidateRect(hWnd, NULL, TRUE);
			UpdateWindow(hWnd);
		}
	}

	UnregisterClass(szWindowClassName, winclass.hInstance);
	return 0;
}