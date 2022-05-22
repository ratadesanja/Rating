#pragma once

#include <string>
#include <vector>
#include <Windows.h>

#include "Console.h"

using std::string;
using std::vector;

struct COORDS
{
	float x = 0, y = 0, z = 0;
};

enum BuffType {
	Internal = 0,
	Aura = 1,
	CombatEnchancer = 2,
	CombatDehancer = 3,
	SpellShield = 4,
	Stun = 5,
	Invisibility = 6,
	Silence = 7,
	Taunt = 8,
	Polymorph = 9,
	Slow = 10,
	Snare = 11,
	Damage = 12,
	Heal = 13,
	Haste = 14,
	SpellImmunity = 15,
	PhysicalImmunity = 16,
	Invulnerability = 17,
	SLEEP = 18,
	NearSight = 19,
	Frenzy = 20,
	Fear = 21,
	Charm = 22,
	Poison = 23,
	Suppression = 24,
	Blind = 25,
	Counter = 26,
	Shred = 27,
	Flee = 28,
	Knockup = 29,
	Knockback = 30,
	Disarm = 31
};

struct BUFF
{
	string name;
	int count;
	float end_time;
	BuffType type = Internal;
};
class Champion
{
	public:
		DWORD POINTER;
		UINT ADDRESS;

		string Name;

		COORDS Pos;

		int Lvl;
		float Health;
		float MaxHealth;
		float Mana;
		float MaxMana;
		float Armor;
		float BonusArmor;
		float MagicRes;
		float BonusMagicRes;

		int MoveSpeed;

		float BaseAtk;
		float BonusAtk;
		float BaseAtkSpeed;
		float AtkSpeedMulti;
		float AtkSpeed;
		float Crit;
		float CritMulti;
		float AtkRange;

		int AbilityHaste;
		int Lethality;

		bool Visibility;
		bool Targetable;
		bool Invulnerable;

		float AbilityPower;
		float AdditionalApMulti;

		float MagicPen;
		float MagicPenMulti;

		float Expiry;
		int IsMoving;
		int Direction;
		int ItemList;
		int Experience;
		int ManaRegen;
		int HealthRegen;

		int Index;
		int Team;
		int NetworkID;
		int SpawnCount;
		int SrcIndex;
		int RecallState;
		vector<BUFF> buffs;

		bool UncappedAS;
		bool IsAlive;

		void UpdateStats();
    	void ShowStats(Console&);
		
		Champion(DWORD, DWORD);
};
void GetChampionNamesFromFile();
vector<Champion> GetChampionlist();

template<typename T> 
T Read(UINT, int, T);
string ReadString(UINT, int, string);

extern vector<Champion> CHAMPION_LIST;
extern vector<int> ALLY_INDEXES;
extern vector<int> ENEMY_INDEXES;