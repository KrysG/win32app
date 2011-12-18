// Task 1: Create a Window
//         Set up DirectX

#define WIN32_LEAN_AND_MEAN
#define STRICT

#include <windows.h>
#include <windowsx.h>
//#include <stdlib.h>
#include <tchar.h>
//#include <stdio.h>
//#include <math.h>
#include <d3d9.h>

// include the Direct3D Library file
#pragma comment (lib, "d3d9.lib")

// Defines

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// Global declarations
LPDIRECT3D9 d3d;	// pointer to Direct3D interface
LPDIRECT3DDEVICE9 d3ddev;	// pointer to the device class

//function prototypes
void initD3D(HWND hWnd);	// stes up and initializes Direct3D
void render_frame(void);	// renders a single frame
void cleanD3D(void);		// closes Direct3D and releases memory

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

	ZeroMemory(&wcex, sizeof(WNDCLASSEX));	

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
	ShowWindow(hWnd,nCmdShow);
	initD3D(hWnd);
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

		render_frame();

		// main game processing goes here
	}

	// clean up DirectX
	cleanD3D();
	
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

//To do: write a wraper for this section

//this function prepares Direct3D for use
void initD3D(HWND hWnd)
{
    d3d = Direct3DCreate9(D3D_SDK_VERSION);    // d3d interface

    D3DPRESENT_PARAMETERS d3dpp;    // create a struct to hold various device information

    ZeroMemory(&d3dpp, sizeof(d3dpp));    // clear out the struct for use
    d3dpp.Windowed = TRUE;    // program windowed, not fullscreen
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;    // discard old frames
    d3dpp.hDeviceWindow = hWnd;    // set the window to be used by Direct3D

    // create a device class using this information and information from the d3dpp stuct
    d3d->CreateDevice(D3DADAPTER_DEFAULT,
                      D3DDEVTYPE_HAL,
                      hWnd,
                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                      &d3dpp,
                      &d3ddev);
}

// this is the function used to render a single frame
void render_frame(void)
{
    // clear the window to a deep blue
    d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 40, 100), 1.0f, 0);

    d3ddev->BeginScene();    // begins the 3D scene

    // do 3D rendering on the back buffer here

    d3ddev->EndScene();    // ends the 3D scene

    d3ddev->Present(NULL, NULL, NULL, NULL);    // displays the created frame
}

// this is the function that cleans up Direct3D and COM
void cleanD3D(void)
{
    d3ddev->Release();    // close and release the 3D device
    d3d->Release();    // close and release Direct3D
}

