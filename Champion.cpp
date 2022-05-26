#include "Champion.h"
#include "Offsets.h"
#include "League.h"
#include "Console.h"
#include "World.h"

#include <Windows.h>
#include <iostream>
#include <fstream>
#include <cmath>
//#include <vector>

using std::cout; using std::endl; //using std::vector;

vector<Champion> CHAMPION_LIST(0);
vector<int> ALLY_INDEXES(0);
vector<int> ENEMY_INDEXES(0);

template <typename T>
T Read(UINT ADDRESS, int offset, T variable)
{
	T var = variable;
	ReadProcessMemory(LeaguePHandle, (LPVOID)(ADDRESS + offset), &var, sizeof(var), nullptr);
	return var;
}

string ReadString(UINT ADDRESS, int offset, string variable)
{
	string var = "";
	UINT StringPTR = 0;
	StringPTR = Read(ADDRESS, offset, StringPTR);
	char buf[255];
	ReadProcessMemory(LeaguePHandle, (LPVOID)StringPTR, &buf, sizeof(buf), nullptr);
	for (int i = 0; i < 100; i++)
	{
		if (buf[i] == NULL)
			break;

		var.push_back(buf[i]);
	}
	return var;
}

BUFF ReadBuff(UINT address)
{
	if (address == 0)
		return { "", 0, 0};


	int info, count;
	float endTime;
	info = 0; count = 0; endTime = 0.0f;
	string name = "";
	unsigned char type = ' ';

	info = Read(address, oBuffEntryBuff, info);
	if (info == 0)
		return { "", 0, 0};


	name = ReadString(address, oBuffName, name); name = name.erase(0, 4);
	count = Read(address, oBuffEntryBuffCount, count);
	endTime = Read(address, oBuffEntryBuffEndTime, endTime);
	type = Read(address, oBuffType, type);

	BuffType bType = (BuffType)type;

	return { name, count, endTime, bType };
	
}

vector<BUFF> ReadBuffs(UINT championAddress)
{
	vector<BUFF> buffs;
	UINT buffsStart = 0; 
	buffsStart = Read(championAddress, oObjBuffManager + oBuffManagerEntriesArray, buffsStart);

	UINT buffsEnd = 0;
	buffsEnd = Read(championAddress, oObjBuffManager + oBuffManagerEntriesArray + 0x4, buffsEnd);

	UINT currentAddress = buffsStart;

	UINT buffPointer = 0;
	while (currentAddress != buffsEnd)
	{
		buffPointer = Read(currentAddress, 0, buffPointer);
		BUFF buff = ReadBuff(buffPointer);
			if(buff.end_time != 0)
			buffs.push_back(buff);
		currentAddress += 0x8;
	}
	return buffs;
}

void Champion::UpdateStats()
{
	Name = ReadString(ADDRESS, oObjName, Name);
	Team = Read(ADDRESS, oObjTeam, Team);

	Visibility = Read(ADDRESS, oObjVisibility, Visibility);
	SpawnCount = Read(ADDRESS, oObjSpawnCount, Invulnerable);
	IsAlive = SpawnCount % 2 == 0 ? true : false;
	if (Visibility && IsAlive)
	{

		Pos = Read(ADDRESS, oObjPos, Pos);
		Lvl = Read(ADDRESS, oObjLvl, Lvl);

		Health = Read(ADDRESS, oObjHealth, Health);
		MaxHealth = Read(ADDRESS, oObjMaxHealth, MaxHealth);
		HealthRegen = Read(ADDRESS, oObjHealthRegen, HealthRegen);

		Mana = Read(ADDRESS, oObjMana, Mana);
		MaxMana = Read(ADDRESS, oObjMaxMana, MaxMana);
		ManaRegen = Read(ADDRESS, oObjManaRegen, ManaRegen);

		Armor = Read(ADDRESS, oObjArmor, Armor);
		BonusArmor = Read(ADDRESS, oObjBonusArmor, BonusArmor);
		MagicRes = Read(ADDRESS, oObjMagicRes, MagicRes);
		BonusMagicRes = Read(ADDRESS, oObjBonusMagicRes, BonusMagicRes);
		MoveSpeed = Read(ADDRESS, oObjMoveSpeed, MoveSpeed);

		BaseAtk = Read(ADDRESS, oObjBaseAtk, BaseAtk);
		BonusAtk = Read(ADDRESS, oObjBonusAtk, BonusAtk);
		AtkSpeedMulti = Read(ADDRESS, oObjAtkSpeedMulti, AtkSpeedMulti);
		Crit = Read(ADDRESS, oObjCrit, Crit);
		CritMulti = Read(ADDRESS, oObjCritMulti, CritMulti);
		AtkRange = Read(ADDRESS, oObjAtkRange, AtkRange);

		AbilityPower = Read(ADDRESS, oObjAbilityPower, AbilityPower);
		AdditionalApMulti = Read(ADDRESS, oObjAdditionalApMulti, AdditionalApMulti);

		MagicPen = Read(ADDRESS, oObjMagicPen, MagicPen);
		MagicPenMulti = Read(ADDRESS, oObjMagicPenMulti, MagicPenMulti);

		AbilityHaste = Read(ADDRESS, oObjAbilityHaste, AbilityHaste);
		Lethality = Read(ADDRESS, oObjLethality, Lethality);

		Targetable = Read(ADDRESS, oObjTargetable, Targetable);
		Invulnerable = Read(ADDRESS, oObjInvulnerable, Invulnerable);

		Index = Read(ADDRESS, oObjIndex, Index);
		NetworkID = Read(ADDRESS, oObjNetworkID, NetworkID);

		Expiry = 0;
		IsMoving = 0;
		Direction = 0;
		ItemList = 0;
		Experience = 0;

		SrcIndex = 0;
		RecallState = 0;

		buffs = ReadBuffs(ADDRESS);

		int HoB = 0;
		int reduction = 0;
		UncappedAS = false;
		for (int i = 0; i < buffs.size(); i++)
		{
			if (buffs[i].name == "ASSETS/Perks/Styles/Precision/LethalTempo/LethalTempo.lua")
			{
				if (buffs[i].count == 6)
					UncappedAS = true;
			}
			if (buffs[i].name == "ASSETS/Perks/Styles/Domination/HailOfBlades/HailOfBladesBuff.lua")
			{
				if (buffs[i].end_time > GAME_TIME)
				{
					UncappedAS = true;
				}
			}
			else if (buffs[i].name == "ASSETS/Perks/Styles/Domination/HailOfBlades/HailOfBladesReady.lua")
			{
				if (buffs[i].end_time > GAME_TIME)
				{
					UncappedAS = true;
					HoB = 1.1;

				}
			}
			if (Name == "Jinx")
			{
				if (buffs[i].name == "jinxpassivekill")
				{
					if (buffs[i].end_time > GAME_TIME)
					{
						UncappedAS = true;
					}
				}
				if (buffs[i].name == "JinxQ")
				{
					if (buffs[i].end_time > GAME_TIME)
					{
						reduction = 10;
					}
				}
			}
		}
		AtkSpeed = BaseAtkSpeed * (AtkSpeedMulti + HoB);
		AtkSpeed = UncappedAS ? AtkSpeed : (AtkSpeed > 2.5) ? 2.5 : AtkSpeed;
		if (reduction != 0)
		{
			AtkSpeed = (AtkSpeed / 100) * (100 - reduction);
		}
		
	}
}

int count_digit(int number) {
   return int(log10(number) + 3);
}

void Champion::ShowStats(Console& console)
{
	int Xstart = 32 + 10;
	int eX;

	cout.precision(2);

	console.Clear(Xstart, Name.length(), 1);
	cout << Name;

	eX = count_digit((int)Pos.x); eX += 10 - eX;
	console.Clear(Xstart, eX, 3);
	cout << std::fixed << Pos.x;

	eX = count_digit((int)Pos.y); eX += 10 - eX;
	console.Clear(Xstart, eX, 4);
	cout << std::fixed << Pos.y;

	eX = count_digit((int)Pos.z); eX += 10 - eX;
	console.Clear(Xstart, eX, 5);
	cout << std::fixed << Pos.z;

	console.Clear(Xstart, count_digit(AtkRange) + 2, 7);
	cout << AtkRange;

	//LethalTempo check
	console.Clear(Xstart, count_digit(AtkSpeed), 9);
	cout << AtkSpeed;

	console.Clear(Xstart, 5, 10);
	if (UncappedAS)
		cout << "true";
	else
		cout << "false";
	
	/*
	for (int i = 0; i < ENEMY_INDEXES.size(); i++)
	{
		int index = ENEMY_INDEXES[i];
		console.Clear((Xstart + i * 6), 5, 12);
		cout << CHAMPION_LIST[index].Visibility << " ";

	}
	*/
	//Show buffs
	/*
	int j = 0;
	for (int i = 0; i < buffs.size(); i++)
	{
		int startY = 11;

		int nameX = buffs[i].name.length();
		int countX = count_digit((int)buffs[i].count); eX += 10 - eX;
		int endX = count_digit((int)buffs[i].end_time); eX += 10 - eX;

		console.Clear(32, nameX + countX + endX + 3, startY + j + 1);
		cout << buffs[i].name << " " << buffs[i].count << " " << buffs[i].end_time;
		j++;
	}
	*/
	
	

}

float GetBaseAtkSpeed(string name)
{
	std::ifstream file;
	file.open("T:\\Programming\\Hacking\\Rating\\stat_database.txt");
	string line;
	string nameFromFile;

	string b_a_s;
	float base_atk_speed = 0.679f;

	bool matchingName = false;

	while (getline(file, line) && matchingName == false)
	{
		b_a_s, nameFromFile = "";
		

		bool readName = false;
		int i = 0;

		for (i = 0; i < line.length() && readName == false; i++)
		{
			if (line[i] != ' ')
				nameFromFile.push_back(line[i]);
			else
				readName = true;
		}

		if (nameFromFile == name)
		{
			for (i; i < line.length(); i++)
			{
				if (line[i] != ' ')
					b_a_s.push_back(line[i]);
			}
			base_atk_speed = std::stof(b_a_s);

			matchingName = true;
		}
	}

	return base_atk_speed;
}

Champion::Champion(DWORD pointer = 0, DWORD addr = 0)
{	
	if (addr == 0)
	{
		POINTER = pointer;
		ADDRESS = Read(LeagueBaseAddress, pointer, ADDRESS);
	}
	else if (pointer == 0)
	{
		POINTER = pointer;
		ADDRESS = addr;
	}

	BaseAtkSpeed = GetBaseAtkSpeed(Name);
	UpdateStats();
	CHAMPION_LIST.push_back(*this);
}


vector<Champion> GetChampionlist()
{
	return CHAMPION_LIST;
}