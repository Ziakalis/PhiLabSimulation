#include "Render.h"
CRender::CRender(HWND _hWnd)
{
	hWnd = _hWnd;
	pD3D = NULL;
	pD3DDevice = NULL;
	pVertex = NULL;
}
CRender::~CRender()
{
	if (pD3DDevice)
	{
		pD3DDevice->Release();
	}
	if (pD3D)
	{
		pD3D->Release();
	}
}

void CRender::Release()
{
	if (pD3DDevice)
	{
		pD3DDevice->Release();
	}
	if (pD3D)
	{
		pD3D->Release();
	}
}

bool CRender::InitializeD3D()
{
	D3DDISPLAYMODE DisplayMode;

	pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (!pD3D)	return false;

	if (FAILED(pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &DisplayMode))) 
		return false;

	D3DPRESENT_PARAMETERS D3dPp;
	ZeroMemory(&D3dPp, sizeof(D3dPp));
	D3dPp.Windowed = true;
	D3dPp.BackBufferFormat = DisplayMode.Format;
	D3dPp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	if (FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&D3dPp,
		&pD3DDevice)))
		return false;
	return true;
}

bool CRender::CalculateVertex()
{

	unsigned long col = D3DCOLOR_XRGB(255, 255, 255);
	return false;
}

void CRender::RenderScene()
{
	pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(32, 64, 128), 1.0f, 0);
	pD3DDevice->BeginScene();

	pD3DDevice->EndScene();

	pD3DDevice->Present(NULL, NULL, NULL, NULL);
}