#include <ddraw.h>
#include "Singleton.h"
#ifndef _DIRECTDRAW_H_
#define _DIRECTDRAW_H_

class DirectDraw : public Singleton<DirectDraw>
{
public:
	DirectDraw(void);
	~DirectDraw(void);
	int CreateDevice(HWND hWnd,int screenWidth, int screenHeight);
	void RestoreSurfaces();
	void ClearSurface(HWND hWnd);
	void PresentBackBuffer(HWND hWnd);

	LPDIRECTDRAWSURFACE7& GetBackBuffer();
	LPDIRECTDRAW7 GetDirectDrawObject();

	int GetScreenWidth();
	int GetScreenHeight();
	bool GetFullScreen();


private:

	bool m_fullScreen;
	int m_bitDepth;
	int m_screenWidth;
	int m_screenHeight;

	LPDIRECTDRAW7			m_DD;		// The DirectDraw object
	LPDIRECTDRAWCLIPPER		m_clipper;	// Clipper for primary surface
	LPDIRECTDRAWSURFACE7	m_DDS;		// Primary surface
	LPDIRECTDRAWSURFACE7	m_DDSBack;	// Back surface

};

#endif // _DIRECTDRAW_H_
