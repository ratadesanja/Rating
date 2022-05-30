#include "Framework.h"
#include "Over.h"
#include "Paint.h"

#include "League.h"

HINSTANCE hInst;                                // current instance
WCHAR windowTitle[9] = L"Window";                  // The title bar text
LPCSTR targetTitle = "RiotWindowClass"; // "RiotWindowClass"
int width, height;
HWND windowHandle, targetHandle;
Paint paint = Paint();

WNDCLASS overWndClass;
MSG msg;

vector<OVER::TextArg> OVER::TextArguments(0);

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

void OVER::Setup()
{
    targetHandle = LeagueHWND;
	hInst = GetModuleHandle(nullptr);
    const char* className = "Window";

    overWndClass.style = CS_HREDRAW | CS_VREDRAW;
    overWndClass.lpfnWndProc = WndProc;
    overWndClass.cbClsExtra = 0;
    overWndClass.cbWndExtra = 0;
    overWndClass.hInstance = hInst;
    overWndClass.hIcon = 0;
    overWndClass.hCursor = LoadCursor(nullptr, IDC_CROSS);
    overWndClass.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
    overWndClass.lpszMenuName = className;
    overWndClass.lpszClassName = className;
    overWndClass.hIcon = 0;

    RegisterClass(&overWndClass);

    RECT rect;
    GetWindowRect(targetHandle, &rect);
    width = rect.right - rect.left;
    height = rect.bottom - rect.top;

    windowHandle = CreateWindowExW(WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED, windowTitle, windowTitle, WS_POPUP, 1, 1, width, height, nullptr, nullptr, hInst, nullptr);

    if (!windowHandle)
    {
        return;
    }

    paint = Paint(windowHandle, targetHandle, width, height);
    SetLayeredWindowAttributes(windowHandle, RGB(0, 0, 0), 0, LWA_COLORKEY);

    ShowWindow(windowHandle, SW_SHOW);
    UpdateWindow(windowHandle);

    return;
}

bool OVER::ProcessMessages()
{
    PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE);
    {
        if (msg.message == WM_QUIT)
        {
            return false;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        //Sleep(33);
    }

    return true;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
    {
        paint.render(OVER::TextArguments);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        //UnregisterClass(&wndClass, hInst);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
}

