#include <iostream>
#include <vector>

#include <Windows.h>
#include <chrono>
#include <thread>

#include "Console.h"
#include "League.h"
#include "Offsets.h"
#include "Champion.h"
#include "World.h"
#include "Orbwalker.h"

#pragma comment (lib, "winmm.lib")

using std::cout; using std::endl; using std::string; using std::vector;

void UpdateInfo()
{
    using namespace std::literals::chrono_literals;

    cout << "Starting thread";
    while (GetGameState())
    {
        FindGameTime();
        for (int i = 0; i < CHAMPION_LIST.size(); i++)
        {
            CHAMPION_LIST[i].UpdateStats();
        }
        std::this_thread::sleep_for(20ms);
    }

}

int main()
{
    //Sleep(3 * 1000);
    Console console;
    console.ShowConsoleCursor(false);

    if (InitLeagueVariables())
    {
        GetChampionNamesFromFile();


        while (FindGameTime() < 30)
        {
            Sleep(1000);
        }
        Champion LocalPlayer(oLocalPlayer, 0);
        GetTeamChampions();
        cout << "Starting game" << endl;

        std::thread updater(UpdateInfo);
        Sleep(1000);

        string sound = "S:\\Guitar\\Split\\Downloads\\sound2.wav";

        int startX = 32;
        console.SetCursorPosition(startX + 2, 1);
        cout << "Name";

        console.SetCursorPosition(startX, 4);
        cout << "Position";

        console.SetCursorPosition(startX, 7);
        cout << "AtkRange";

        console.SetCursorPosition(startX, 9);
        cout << "AtkSpeed";
        console.SetCursorPosition(startX, 10);
        cout << "Uncapped";

        bool targetChampionsOnly = false;

        while (GAME_STATE)
        {
            /*
            LocalPlayer.UpdateStats();
            for (int i = 0; i < CHAMPION_LIST.size(); i++)
            {
                CHAMPION_LIST[i].UpdateStats();
            }
            */
            CHAMPION_LIST[0].ShowStats(console);
            if (GetAsyncKeyState(0x58))
            {
                break;
            }
            if (GetAsyncKeyState(VK_SPACE))
            {
                console.Clear(0, 64, 15);
                if (!targetChampionsOnly)
                {
                    targetChampionsOnly = TargetChampionsOnly(targetChampionsOnly, true);
                    PlaySound(sound.c_str(), NULL, SND_FILENAME | SND_ASYNC);
                }

                /*
                using std::chrono::duration_cast;
                using std::chrono::milliseconds;
                using std::chrono::seconds;
                using std::chrono::system_clock;
                auto millisec_since_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
                */

                Attack();
                //auto funcTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - millisec_since_epoch;

                //LocalPlayer.UpdateStats();
                console.Clear(0, 9, 16);
                cout << "ON"; //<< " " << funcTime;
            }
            else if (!GetAsyncKeyState(VK_SPACE))
            {
                PlaySound(NULL, NULL, SND_ASYNC);
                console.Clear(0, 3, 16);
                cout << "OFF";
                if (targetChampionsOnly)
                    targetChampionsOnly = TargetChampionsOnly(targetChampionsOnly, false);
            }

            Sleep(34);
        }
        updater.join();
        cout << endl << "Game ended." << endl;
    }
    else
    {
        cout << "Game not found" << endl;
    }
    Sleep(2500);
    return 0;
}