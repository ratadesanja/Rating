#include "Champion.h"
#include "Orbwalker.h"
#include "World.h"

#include "Mouse.h"

#include <iostream>

// windupPercentage = 0.2019159823656082; twitch
// windupPercentage = 0.1499999940395355; nida
// 0.3 jinx
// 0.14800000488758086 trist
// 0.1754385933279991 vayne
// 

float attackSpeed = 0;
float attackSpeedBase = 0;
float windupPercentage = 0.3;
float canAttackTime = 0;
float canMoveTime = 0;

float PING = 38 / 1000;

float GetAttackDelay(float atkSpeed)
{
	float attackDelay = 1 / atkSpeed;
    return attackDelay;
}
 
float GetWindupTime(float atkTime, float atkSpeedBase)
{

	float baseWindupTime = (1 / atkSpeedBase) * windupPercentage;
	float windupTime = baseWindupTime + ((atkTime * windupPercentage) - baseWindupTime) * (1+0);

	float minValue = (atkTime < windupTime) ? atkTime : windupTime;

    return minValue;
}

bool TargetChampionsOnly(bool isOn, bool value)
{
	if (isOn)
	{
		if (value)
		{
			return true;
		}
		else
		{
			MoveMouse(0, 0, 1, 3);
			return false;
		}
	}
	else
	{
		if (value)
		{
			MoveMouse(0, 0, 0, 3);
			return true;
		}
		else
		{
			return false;
		}

	}
}

void Attack()
{
	int targetIndex = -1;
	//targetIndex = FindClosestTarget();
	targetIndex = FindLowestTarget();
	FindGameTime();
	if (targetIndex > -1)
	{
		for (int i = 0; i < CHAMPION_LIST[0].buffs.size(); i++)
		{
			switch (CHAMPION_LIST[0].buffs[i].type)
			{
			case Stun:
			case Taunt:
			case Polymorph:
			case Snare:
			case SLEEP:
				//case NearSight:
			case Fear:
			case Charm:
			case Suppression:
			case Blind:
				//case Disarm:
				if (CHAMPION_LIST[0].buffs[i].end_time > GAME_TIME)
				{
					SendKey(33);
					//std::cout << champion_list[0].buffs[i].name << std::endl;
				}
			}
		}


		attackSpeed = CHAMPION_LIST[0].AtkSpeed;// / 100 * 80;
		attackSpeedBase = CHAMPION_LIST[0].BaseAtkSpeed;

		COORDS target = CHAMPION_LIST[targetIndex].Pos;

		COORDS screenPos = World2Screen(target.x, target.y, target.z);

		
		if (screenPos.x > 0 && screenPos.x < SCREEN_WIDTH && screenPos.y > 0 && screenPos.y < SCREEN_HEIGHT)
		{
			std::cout << "Closest Target: " << CHAMPION_LIST[targetIndex].Name << " - " << screenPos.x << " " << screenPos.y;
			POINT p;
			GetCursorPos(&p);
			if (canAttackTime < GAME_TIME)
			{
				MoveMouse(screenPos.x, screenPos.y, 1, 0);
				Sleep(10);

				//FindGameTime();
				float atkDelay = GetAttackDelay(attackSpeed);
				canAttackTime = GAME_TIME + atkDelay + PING;
				canMoveTime = GAME_TIME + GetWindupTime(atkDelay, attackSpeedBase) + PING;

				MoveMouse(p.x, p.y, 0, 1);
				Sleep(15);

			}
			if (canMoveTime < GAME_TIME)
			{
				MoveMouse(0, 0, 1, 2);
				canMoveTime = GAME_TIME + PING;
			}
		}
		else
		{
			POINT p;
			GetCursorPos(&p);
			MoveMouse(p.x, p.y, 1, 0);
			std::cout << "no targets";
		}
	}
	else
	{
		POINT p;
		GetCursorPos(&p);
		MoveMouse(p.x, p.y, 1, 0);
		std::cout << "no targets";
	}
}