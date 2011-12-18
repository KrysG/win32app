// Task 1: Create a Window
//         Set up DirectX

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <tchar.h>
#include <stdio.h>
#include <math.h>

// Defines

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// Global variables

// The main window class name.
static TCHAR szWindowClass[] = _T("win32app");

// The string that appears in the application's title bar.
static TCHAR szTitle[] = _T("Win32 Application");

HINSTANCE hInst;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


int WINAPI WinMain(HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine,
				   int nCmdShow)
{
	WNDCLASSEX wcex;
	

	wcex.cbSize			= sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	
	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Win32 Application"),
			NULL);

		return 1;
	}

	hInst = hInstance;

	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);

	if(!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Win32 Application"),
			NULL);

		return 1;
	}

	// The parameters to ShowWindow explained:
	// hWnd: the value returned from CreateWindow
	// nCmdShow: the fourth parameter from WinMain
	// Game initialization goes here
	ShowWindow(hWnd,
		nCmdShow);
	UpdateWindow(hWnd);

	// Main message loop:
	MSG msg;
	while(TRUE)
	{
		// is there a message in queue, if so get it
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// main game processing goes here
	}

	return (int) msg.wParam;	

}



LRESULT CALLBACK WndProc(HWND hWnd, 
						 UINT message, 
						 WPARAM wParam, 
						 LPARAM lParam)
{	// this is the main message handler
	
	HDC hdc;		// handle do a device context
	PAINTSTRUCT ps; // used in WM_PAINT

	switch(message)
	{
	case WM_CREATE:
		{
			// initialization stuff here

			return 0;
		}break;

	case WM_PAINT:
		{
			hdc = BeginPaint(hWnd, &ps);

			return 0;
		}break;

	case WM_KEYDOWN:
		{
			if(wParam == VK_ESCAPE)
			{
				int ret = MessageBox(NULL, _T("Exit program?"), _T("Question"), MB_OKCANCEL);
				if(ret == IDOK)
					SendMessage(hWnd, WM_CLOSE,0,0);
			}

		}break;

	case WM_DESTROY:
		{
			PostQuitMessage(0); // kill the application, sends a WM_QUIT message

			return 0;
		}break;

	default:break;
	}

	return (DefWindowProc(hWnd, message, wParam, lParam));

}
