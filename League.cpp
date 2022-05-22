#include <Windows.h>
#include <TlHelp32.h>
#include <tchar.h>

#include "League.h"

HWND LeagueHWND = NULL;
DWORD LeaguePID = NULL;
HANDLE LeaguePHandle = NULL;
DWORD LeagueBaseAddress = NULL;

bool InitLeagueVariables()
{
    LeagueHWND = FindWindowA("RiotWindowClass", nullptr);
    if (LeagueHWND != NULL)
    {
        GetWindowThreadProcessId(LeagueHWND, &LeaguePID);
        LeaguePHandle = OpenProcess(PROCESS_ALL_ACCESS, false, LeaguePID);

        char game_name[22] = "League of Legends.exe";

        HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, LeaguePID);
        DWORD dwModuleBaseAddress = 0;
        if (hSnapshot != INVALID_HANDLE_VALUE)
        {
            MODULEENTRY32 ModuleEntry32 = { 0 };
            ModuleEntry32.dwSize = sizeof(MODULEENTRY32);
            if (Module32First(hSnapshot, &ModuleEntry32))
            {
                do
                {
                    if (strcmp(ModuleEntry32.szModule, game_name) == 0)
                    {
                        dwModuleBaseAddress = (DWORD)ModuleEntry32.modBaseAddr;
                        break;
                    }
                } while (Module32Next(hSnapshot, &ModuleEntry32));
            }
            CloseHandle(hSnapshot);
        }
        LeagueBaseAddress = dwModuleBaseAddress;
        return true;
    }
    else
    {
        return false;
    }
}