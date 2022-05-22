#pragma once
#include <Windows.h>

void GetTeamChampions();
int* World2Screen(float, float, float);

int FindClosestTarget();
int FindLowestTarget();

extern float GAME_TIME;
extern bool GAME_STATE;

float FindGameTime();
bool GetGameState();