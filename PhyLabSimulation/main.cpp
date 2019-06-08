#include <Windows.h>
#include "CustomScene.h"
#define M_WND_CLASSNAME "DX_Wnd"
#define M_WND_TITLE		"PhyLab Simulation"
#define M_WND_WIDTH		1024
#define M_WND_HEIGHT	768

LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		break;
	case WM_KEYUP:
		if (wParam == VK_ESCAPE)
		{
			PostQuitMessage(0);
			return 0;
		}
		break;
	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE prevInst, LPTSTR cmdLine, int show)
{
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0, 0, hInst, NULL, NULL, NULL, NULL, M_WND_CLASSNAME, NULL };

	RegisterClassEx(&wc);

	HWND hWnd = CreateWindow(M_WND_CLASSNAME, M_WND_TITLE, WS_OVERLAPPEDWINDOW, 300, 100, M_WND_WIDTH, M_WND_HEIGHT, GetDesktopWindow(), NULL, hInst, NULL);

	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	FILE* pf;
	fopen_s(&pf, "Record.txt", "w");
	if (!pf) return 0;
	fprintf_s(pf, "Time SX SY SZ SVx SVy SVz SAx SAy SAz EX EY EZ EVx EVy EVz EAx EAy EAz\n");

	CScene MainScene(InitializeMainScene, DynamicCalculation);
	MainScene.InitializeScene();

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			MainScene.DynamicCalculation();
			MainScene.KinematicCalculation();
			fprintf_s(pf, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f\n",
				MainScene.SimuTime,
				MainScene.ppElementList[1]->Pos.x,
				MainScene.ppElementList[1]->Pos.y,
				MainScene.ppElementList[1]->Pos.z,
				MainScene.ppElementList[1]->Vel.x,
				MainScene.ppElementList[1]->Vel.y,
				MainScene.ppElementList[1]->Vel.z,
				MainScene.ppElementList[1]->Acc.x,
				MainScene.ppElementList[1]->Acc.y,
				MainScene.ppElementList[1]->Acc.z,
				MainScene.ppElementList[0]->Pos.x,
				MainScene.ppElementList[0]->Pos.y,
				MainScene.ppElementList[0]->Pos.z,
				MainScene.ppElementList[0]->Vel.x,
				MainScene.ppElementList[0]->Vel.y,
				MainScene.ppElementList[0]->Vel.z,
				MainScene.ppElementList[0]->Acc.x,
				MainScene.ppElementList[0]->Acc.y,
				MainScene.ppElementList[0]->Acc.z);

			if (MainScene.SimuTime >= MainScene.StopTime)
			{
				PostQuitMessage(0);
			}
		}
	}

	UnregisterClass(M_WND_CLASSNAME, hInst);

	return 0;
}