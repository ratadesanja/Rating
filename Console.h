#pragma once
#include <Windows.h>

class Console
{

    public:
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD size;


        void ShowConsoleCursor(bool);


        void SetCursorPosition(int, int);


        COORD GetCursorPosition();

        void Clear(int, int, int);

        void GetConsoleSize();


        void SetColor(int);


        void SetFullscreen();
};