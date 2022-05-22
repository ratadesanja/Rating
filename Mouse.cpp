#include "Mouse.h"


//#include <iostream>

double fScreenWidth = ::GetSystemMetrics(SM_CXSCREEN) - 1;
double fScreenHeight = ::GetSystemMetrics(SM_CYSCREEN) - 1;

void MoveMouse(int x, int y, int button, int action)
{
	double dX = x * (65535.0f / fScreenWidth);
	double dY = y * (65535.0f / fScreenHeight);
	if (action == 0)
	{
		INPUT input[3] = {};
		input[0].type = INPUT_MOUSE;
		input[0].mi.dx = dX;
		input[0].mi.dy = dY;
		input[0].mi.dwFlags = (MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE); // (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE | MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP)

		if (button == 0)
		{

			input[1].type = INPUT_MOUSE;
			input[1].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

			input[2].type = INPUT_MOUSE;
			input[2].mi.dwFlags = MOUSEEVENTF_LEFTUP;
		}
		else
		{
			input[1].type = INPUT_MOUSE;
			input[1].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;

			input[2].type = INPUT_MOUSE;
			input[2].mi.dwFlags = MOUSEEVENTF_RIGHTUP;
		}
		UINT uS = SendInput(3, input, sizeof(INPUT));
		ZeroMemory(input, sizeof(INPUT));
	}
	else if (action == 1)
	{
		INPUT input[1] = {};
		input[0].type = INPUT_MOUSE;
		input[0].mi.dx = dX;
		input[0].mi.dy = dY;
		input[0].mi.dwFlags = (MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE); // (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE | MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP)
		UINT uS = SendInput(1, input, sizeof(INPUT));
		ZeroMemory(input, sizeof(INPUT));
	}
	else if (action == 2)
	{
		INPUT input[2] = {};
		if (button == 0)
		{

			input[0].type = INPUT_MOUSE;
			input[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

			input[1].type = INPUT_MOUSE;
			input[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
		}
		else
		{
			input[0].type = INPUT_MOUSE;
			input[0].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;

			input[1].type = INPUT_MOUSE;
			input[1].mi.dwFlags = MOUSEEVENTF_RIGHTUP;
		}
		UINT uS = SendInput(2, input, sizeof(INPUT));
		ZeroMemory(input, sizeof(INPUT));
	}
	else if (action == 3)
	{
		if (button == 0)
		{
			INPUT input[1] = {};
			input[0].type = INPUT_MOUSE;
			input[0].mi.dwFlags = (MOUSEEVENTF_MIDDLEDOWN); // (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE | MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP)
			UINT uS = SendInput(1, input, sizeof(INPUT));
			ZeroMemory(input, sizeof(INPUT));
		}
		else
		{
			INPUT input[1] = {};
			input[0].type = INPUT_MOUSE;
			input[0].mi.dwFlags = (MOUSEEVENTF_MIDDLEUP); // (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE | MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP)
			UINT uS = SendInput(1, input, sizeof(INPUT));
			ZeroMemory(input, sizeof(INPUT));

		}
	}
}

void SendKey(WORD scanCode)
{
	INPUT input[1] = { 0 };
	input[0].type = INPUT_KEYBOARD;
	input[0].ki.wVk = NULL;
	input[0].ki.wScan = scanCode;
	input[0].ki.dwFlags = KEYEVENTF_SCANCODE;

	UINT ret = SendInput(1, input, sizeof(INPUT));

	Sleep(10);

	input[0] = { 0 };
	input[0].type = INPUT_KEYBOARD;
	input[0].ki.wVk = NULL;
	input[0].ki.wScan = scanCode;
	input[0].ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;


	ret = SendInput(1, input, sizeof(INPUT));
}
/*
int main()
{
	Sleep(1000);
	SendKey(33);
	return 0;
}
*/