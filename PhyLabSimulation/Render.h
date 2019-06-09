#pragma once
#include "Scene.h"
#include <malloc.h>
#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

using namespace PhyLabSimu;

struct D3DVertex
{
	float x, y, z, rhw;
	unsigned long color;
};

#define D3DFVF_VERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

class CRender
{
public:
	HWND hWnd;
	LPDIRECT3D9 pD3D;
	LPDIRECT3DDEVICE9 pD3DDevice;
	D3DVertex** pVertex;

	CRender(HWND _hWnd);
	~CRender();
	bool InitializeD3D();
	bool CalculateVertex();
	void RenderScene();
	void Release();
	
};

