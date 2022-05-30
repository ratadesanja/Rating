#include "Paint.h"

int Paint::init(HWND hWND)
{
	if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &object)))
	{
		exit(1);
	}
	ZeroMemory(&params, sizeof(params));

	params.BackBufferWidth = width;
	params.BackBufferHeight = height;
	params.Windowed = true;
	params.hDeviceWindow = hWND;
	params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	params.MultiSampleQuality = D3DMULTISAMPLE_NONE;
	params.BackBufferFormat = D3DFMT_A8R8G8B8;
	params.EnableAutoDepthStencil = TRUE;
	params.AutoDepthStencilFormat = D3DFMT_D16;

	object->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWND, D3DCREATE_HARDWARE_VERTEXPROCESSING, &params, 0, &device);


	D3DXCreateFont(device, 25, 0, FW_LIGHT, 1, false, DEFAULT_CHARSET, OUT_DEVICE_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH, "Century Gothic", &font);

	//D3DXCreateFont(device, 50, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEVICE_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH, "Comic Sans", &font);
	return 0;
}

void Paint::drawText(string str, int x, int y, int a, int r, int g, int b)
{
	char* ptr = &str[0];
	RECT rect;
	rect.top = y;
	rect.left = x;

	font->DrawTextA(0, ptr, str.length(), &rect, DT_NOCLIP, D3DCOLOR_ARGB(a, r, g, b));

}

int Paint::render(vector<OVER::TextArg> TextArguments)
{
	if (device == nullptr)
		return 1;

	device->Clear(0, 0, D3DCLEAR_TARGET, 0, 1.0f, 0);
	device->BeginScene();

	if (TargetHWND == GetForegroundWindow())
	{
		for (int i = 0; i < TextArguments.size(); i++)
		{
			drawText
			(
				TextArguments[i].text, 
				TextArguments[i].x,
				TextArguments[i].y,
				TextArguments[i].a,
				TextArguments[i].r,
				TextArguments[i].g,
				TextArguments[i].b
			);
		}
	}

	device->EndScene();
	device->PresentEx(0, 0, 0, 0, 0);

	return 0;
}

Paint::Paint()
{
}

Paint::Paint(HWND overlayHWND, HWND targetHWND, int width, int height)
{
	this->width = width;
	this->height = height;
	this->TargetHWND = targetHWND;
	init(overlayHWND);
}
