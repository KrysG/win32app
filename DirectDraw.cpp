#include "DirectDraw.h"

// This part Creates a Direct Draw Device in windowed mode.

DefineSingleton(DirectDraw);

DirectDraw::DirectDraw(void)
{
}

DirectDraw::~DirectDraw(void)
{
	m_DDS->Release();
	m_DDSBack->Release();
	m_DD->Release();
}
int
DirectDraw::CreateDevice(HWND hWnd,int screenWidth,int screenHeight)
{
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	HRESULT hRes;
	//Attempts to create a DirectDraw Device
	hRes = DirectDrawCreateEx(NULL,(void**)&m_DD,IID_IDirectDraw7,NULL);
	if (hRes != DD_OK)
	{
		return 0;
	}

	//Stes the CooperativeLevel of the window to a Normal, windowed setting
	hRes = m_DD->SetCooperativeLevel(hWnd,DDSCL_NORMAL);
	if (hRes != DD_OK)
	{
		return 0;
	}

	//DDSURFACEDESC is a structure that contains parameters to create the ddraw surface
	DDSURFACEDESC2 ddsd;
	memset(&ddsd,0, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);

	//full screen requires different parameters than a windows ddraw surface,
	ddsd.dwFlags = DDSD_CAPS;
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

	//this create a render surface that will be seen on screen
	hRes = m_DD->CreateSurface(&ddsd, &m_DDS, NULL);
	if (hRes != DD_OK)
	{
		return 0;
	}

	//with that created, we create the back buffer
	ddsd.dwFlags = DDSD_WIDTH | DDSD_HEIGHT | DDSD_CAPS;
	ddsd.dwWidth = screenWidth + (screenWidth*2);
	ddsd.dwHeight = screenHeight + 200;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;

	hRes = m_DD->CreateSurface(&ddsd, &m_DDSBack, NULL);
	if (hRes != DD_OK)
	{
		return 0;
	}

	//create a cliper that allows other window to overlap the surface
	hRes = m_DD->CreateClipper(0,&m_clipper,NULL);
	if (hRes != DD_OK)
	{
		return 0;
	}

	hRes = m_DDS->SetClipper(m_clipper);
	if (hRes != DD_OK)
	{
		return 0;
	}

	
	if(m_DDSBack)
	{
		hRes = m_DDSBack->Lock(NULL,&ddsd,DDLOCK_WAIT,NULL);
		if (hRes != DD_OK)
		{
			return 0;
		}

		m_bitDepth = ddsd.ddpfPixelFormat.dwRGBBitCount;

		hRes = m_DDSBack->Unlock(NULL);
		if (hRes != DD_OK)
		{
			return 0;
		}
	}
	return 1;
}


void
DirectDraw::ClearSurface(HWND hWnd)
{
	HRESULT hr;
	DDBLTFX ddbfx;
	RECT rcDest;

	//safety net
	if (m_DDSBack == NULL)
		return;

	//initialize the DDBLTFX structure with the pixel color
	ddbfx.dwSize = sizeof(ddbfx);
	ddbfx.dwFillColor = 255;

	//blit rectangle
	hr = m_DDSBack->Blt(NULL,NULL,NULL,DDBLT_WAIT | DDBLT_COLORFILL,&ddbfx);
}

void
DirectDraw::RestoreSurfaces()
{
	if(m_DDS)
	{
		if(m_DDS->IsLost() == DDERR_SURFACELOST)
		{
			m_DDS->Restore();
		}
	}

	if(m_DDSBack)
	{
		if(m_DDSBack->IsLost() == DDERR_SURFACELOST)
		{
			m_DDSBack->Restore();
		}
	}
}

void
DirectDraw::PresentBackBuffer(HWND hWnd)
{

	RECT rcSrc;	// source blit rectangle
	RECT rcDest;// destination blit rectangle
	POINT p;

	//find out where on the primary surface our window lives
	p.x = 0;
	p.y = 0;
	::ClientToScreen(hWnd, &p);
	::GetClientRect(hWnd, &rcDest);
	OffsetRect(&rcDest, p.x, p.y);


	SetRect(&rcSrc, 0 + m_screenWidth, 0, m_screenWidth + m_screenWidth, m_screenHeight);
	m_DDS->Blt(&rcDest,m_DDSBack,&rcSrc,DDBLT_WAIT,NULL);
}

LPDIRECTDRAWSURFACE7&
DirectDraw::GetBackBuffer()
{
	return m_DDSBack;
}

LPDIRECTDRAW7
DirectDraw::GetDirectDrawObject()
{
	return m_DD;
}

int
DirectDraw::GetScreenWidth()
{
	return m_screenWidth;
}

int
DirectDraw::GetScreenHeight()
{
	return m_screenHeight;
}

bool
DirectDraw::GetFullScreen()
{
	return m_fullScreen;
}








