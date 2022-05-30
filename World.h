#pragma once
#include <Windows.h>

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

COORDS World2Screen(float, float, float);

void GetTeamChampions();
int FindClosestTarget();
int FindLowestTarget();

extern float GAME_TIME;
extern bool GAME_STATE;

float FindGameTime();
bool GetGameState();