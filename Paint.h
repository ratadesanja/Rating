#pragma once
#include <Windows.h>

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include "Over.h"

using std::string; using std::vector;

class Paint
{
private:
	IDirect3D9Ex* object = NULL;
	IDirect3DDevice9Ex* device = NULL;
	D3DPRESENT_PARAMETERS params;
	ID3DXFont* font = 0;
	HWND TargetHWND;
	int width, height;

	int init(HWND);

	void drawText(string, int, int, int, int, int, int);

public:
	int render(vector<OVER::TextArg>);

	Paint();
	Paint(HWND, HWND, int, int);
};

