#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

#include "Champion.h"
#include "League.h"
#include "Offsets.h"

using std::cout; using std::endl; using std::vector; using std::string;

struct Node
{
	UINT address = 0;
	Node* next = nullptr;
};

bool IsInList(UINT address, vector<UINT> address_seen)
{
	bool alreadySeen = false;
	for (int i = 0; i < address_seen.size() && alreadySeen == false; i++)
	{
		if (address == address_seen[i])
		{
			alreadySeen = true;
			continue;
		}
	}
	return alreadySeen;
}

/*
void LinkedInsert(Node& currentNode, UINT nextAddress)
{
	Node nextNode = { nextAddress, nullptr };
	if (currentNode.next == nullptr)
		currentNode.next = &nextNode;
}
*/

vector<string> validChampions;
void GetChampionNamesFromFile()
{
	std::ifstream file;
	file.open("T:\\Programming\\Hacking\\Rating\\stat_database.txt");
	string line;
	string nameFromFile;


	while (getline(file, line))
	{
		nameFromFile = "";
		bool readName = false;
		int i = 0;

		for (i = 0; i < line.length() && readName == false; i++)
		{
			if (line[i] != ' ')
				nameFromFile.push_back(line[i]);
			else
			{
				readName = true;
				validChampions.push_back(nameFromFile);
			}
		}

	}
}

bool IsChampionName(string championName)
{
	bool matchingName = false;
	for (int i = 0; i < championName.length(); i++)
	{
		championName[i] = std::tolower(championName[i]);
	}
	for (int i = 0; i < validChampions.size(); i++)
	{
		if (championName == validChampions[i])
		{
			matchingName = true;
			break;
		}
	}
	return matchingName;

}

void FindObjectPointers(vector<UINT>& pointers)
{
	UINT objectManagerPointer = 0;
	objectManagerPointer = Read(LeagueBaseAddress, oObjectManager, objectManagerPointer);

	//UINT objectManager = 0;
	//objectManager = Read(objectManagerPointer, 0, objectManager);

	Node rootNode = { 0, nullptr };
	rootNode = { Read(objectManagerPointer, oObjectMapRoot, rootNode.address), 0 };

	Node* newNode = &rootNode;
	Node* currentNode = newNode;
	Node* iteratorNode = currentNode;
	Node* h = &rootNode;

	vector<UINT> address_seen;

	UINT childAddress = 0;

	int count = 0;

	do
	{
		//cout << currentNode->address << endl;
		int currentObject = 0;
		int currentObjectNetID = 0;
		int currentObjectTeam = 0;
		string currentObjectName = "";


		bool alreadySeen = IsInList(currentNode->address, address_seen);
		if (alreadySeen)
		{
			currentNode = currentNode->next;
			continue;
		}
		else
		{
			address_seen.push_back(currentNode->address);
			count++;
			for (int i = 0; i < 3; i++)
			{
				childAddress = Read(currentNode->address, i * 4, childAddress);
				//childAddress = Read(childAddress, i * 4, childAddress);
				if (!IsInList(childAddress, address_seen))
				{
					newNode = new Node;
					newNode->address = childAddress;
					iteratorNode->next = newNode;
					iteratorNode = iteratorNode->next;
				}

			}

			currentObjectNetID = Read(currentNode->address, oObjectMapNodeNetId, currentObjectNetID);

			if ((currentObjectNetID - 0x40000000) <= 0x100000)
			{
				currentObject = Read(currentNode->address, oObjectMapNodeObject, currentObject);

				currentObjectTeam = Read(currentObject, oObjTeam, currentObjectTeam);
				if (currentObjectTeam == 100 || currentObjectTeam == 200 || currentObjectTeam == 300)
				{
					/*
					currentObjectName = ReadString(currentObject, oObjName, currentObjectName);
					if (currentObjectName.length() < 32 && currentObjectName.length() > 0 || currentObjectName == "Twitch")
					{
						cout << currentObjectName << endl;
						pointers.push_back(currentObject);
					}
					*/
					pointers.push_back(currentObject);
				}

				if (currentObject == 1037154576)
				{
					cout << "Twitch Pointer = " << currentObject << endl;
					//system("pause");
				}
			}

			/*
			*/

		}



		currentNode = currentNode->next;
	} while (currentNode->next != nullptr and count < 800);
}
void FindChampionPointers(vector<Champion>& ChampionList, vector<UINT>& addressSeen)
{
	vector<UINT> pointers;
	FindObjectPointers(pointers);


	for (int i = 0; i < pointers.size(); i++)
	{
		UINT pointer = 0;
		pointer = pointers[i];
		string newChampionName = "";
		float newChampionHealth = 0.0f;
		try
		{


			newChampionName = ReadString(pointer, oObjName, newChampionName);
			if (IsChampionName(newChampionName))
			{
				vector<UINT> addressSeen;
				for (int j = 0; j < CHAMPION_LIST.size(); j++)
				{
					addressSeen.push_back(CHAMPION_LIST[j].ADDRESS);
				}
				if (!IsInList(pointer, addressSeen))
				{
					Champion newChampion(0, pointer);
				}
			}

		}
		catch (...)
		{
			continue;
		}
	}
}

void GetTeamChampions()
{
	vector<UINT> addressSeen;
	string localPlayerName = CHAMPION_LIST[CHAMPION_LIST.size() - 1].Name;
	addressSeen.push_back(CHAMPION_LIST[CHAMPION_LIST.size() - 1].ADDRESS);

	FindChampionPointers(CHAMPION_LIST, addressSeen);

	


	int team = CHAMPION_LIST[0].Team;

	for (int i = 0; i < CHAMPION_LIST.size(); i++)
	{
		//cout << CHAMPION_LIST[i].Name;
		if (CHAMPION_LIST[i].Team == team)
		{
			//cout << " is Ally" << endl;
			ALLY_INDEXES.push_back(i);
		}
		else
		{
			//cout << " is Enemy" << endl;
			ENEMY_INDEXES.push_back(i);
		}
	}

	cout << "Allies:" << endl;

	for (int i = 0; i < ALLY_INDEXES.size(); i++)
	{
		cout << CHAMPION_LIST[ALLY_INDEXES[i]].Name << endl;
	}

	cout << endl << "Enemies:" << endl;

	for (int i = 0; i < ENEMY_INDEXES.size(); i++)
	{
		cout << CHAMPION_LIST[ENEMY_INDEXES[i]].Name << endl;
	}

	cout << endl << endl << endl;
}

int width = 0; int height = 0;
float* VIEWPROJMATRIX = nullptr;

void FindViewProjMatrix()
{
	UINT renderer = 0;
	renderer = Read(LeagueBaseAddress, oRenderer, renderer);

	width = Read(renderer, oRendererWidth, width);
	height = Read(renderer, oRendererHeight, width);

	UINT viewProjMatrices = LeagueBaseAddress + oViewProjMatrices;

	float viewMatrix[4][4] = {};

	float value = 0.0f;
	int i, j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			value = Read(viewProjMatrices, (i * 16 + j * 4), value);
			viewMatrix[i][j] = value;
		}
	}

	float projMatrix[4][4] = {};

	value = 0.0f;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			value = Read(viewProjMatrices, 64 + (i * 16 + j * 4), value);
			projMatrix[i][j] = value;
		}
	}

	float viewProjMatrix[4][4] = {};

	for (i = 0; i < 4; i++)
	{
		for (j = 0; i < 4; i++)
		{
			viewProjMatrix[i][j] = 0.0f;
		}
	}

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				viewProjMatrix[i][j] += viewMatrix[i][k] * projMatrix[k][j];
			}
		}
	}

	float returnViewProjMatrix[16] = {};


	for (i = 0; i < 16; i++)
	{
		returnViewProjMatrix[i] = viewProjMatrix[i/4][i % 4];
	}
	/*
	for (i = 0; i < 16; i++)
	{
		cout << returnViewProjMatrix[i] << endl;
	}
	*/

	VIEWPROJMATRIX = returnViewProjMatrix;

}

int* World2Screen(float x, float y, float z)
{
	/*
	if (VIEWPROJMATRIX == nullptr)
	{
		FindViewProjMatrix();
	}
	*/
	FindViewProjMatrix();
	float* viewProjMatrix = VIEWPROJMATRIX;

	float clipCoordsX, clipCoordsY, clipCoordsW;
	float Mx, My;
	int outX, outY;

	clipCoordsX = x * viewProjMatrix[0] + y * viewProjMatrix[4] + z * viewProjMatrix[8] + viewProjMatrix[12];
	clipCoordsY = x * viewProjMatrix[1] + y * viewProjMatrix[5] + z * viewProjMatrix[9] + viewProjMatrix[13];
	clipCoordsW = x * viewProjMatrix[3] + y * viewProjMatrix[7] + z * viewProjMatrix[11] + viewProjMatrix[15];

	if (clipCoordsW < 1)
		clipCoordsW = 1.;

	Mx = clipCoordsX / clipCoordsW;
	My = clipCoordsY / clipCoordsW;

	outX = (width / 2. * Mx) + (Mx + width / 2.);
	outY = -(height / 2. * My) + (My + height / 2.);

	int output[2] = {0, 0};

	if (0 <= outX <= width && 0 <= outY <= height)
	{
		output[0] = outX;
		output[1] = outY;
	}

	return output;

}

int FindClosestTarget()
{
	vector<Champion> champion_list = GetChampionlist();
	float closestX = 16000, closestZ = 16000;
	float closestDistance = closestX + closestZ;
	float radius = 0;
	int closestIndex = -1;
	float localPlayerX = champion_list[0].Pos.x, localPlayerZ = champion_list[0].Pos.z;
	int localPlayerTeam = champion_list[0].Team;
	int localPlayerRange = champion_list[0].AtkRange;// -2;

	for (int i = 1; i < champion_list.size(); i++)
	{
		bool targetVisible = champion_list[i].Visibility;
		bool targetInvulnerable = champion_list[i].Invulnerable;
		int targetTeam = champion_list[i].Team;
		float targetHealth = champion_list[i].Health;
		if (targetTeam != localPlayerTeam && targetHealth > 1 && targetVisible && !targetInvulnerable)
		{
			float targetX = champion_list[i].Pos.x, targetZ = champion_list[i].Pos.z;
			float distance = abs(targetX - localPlayerX) + abs(targetZ - localPlayerZ);

			if(distance < localPlayerRange )

				if (distance < closestDistance)
				{
					closestDistance = distance;
					closestIndex = i;
				}
				if (closestDistance < 200)
					break;
		}
	}
	return closestIndex;
}

int FindLowestTarget()
{
	int lowestIndex = -1;
	float localPlayerX = CHAMPION_LIST[0].Pos.x, localPlayerZ = CHAMPION_LIST[0].Pos.z;
	int localPlayerRange = (CHAMPION_LIST[0].AtkRange / 100) * 90;

	float lowestHealth = 16000;
	int lowestArmor = 10000;

	for (int i = 0; i < ENEMY_INDEXES.size(); i++)
	{
		int index = ENEMY_INDEXES[i];
		bool targetVisible = CHAMPION_LIST[index].Visibility;
		bool targetInvulnerable = CHAMPION_LIST[index].Invulnerable;
		bool targetAlive = CHAMPION_LIST[index].IsAlive;

		if (targetAlive && targetVisible && !targetInvulnerable)
		{
			float targetX = CHAMPION_LIST[index].Pos.x, targetZ = CHAMPION_LIST[index].Pos.z;

			float distance = (abs(targetX - localPlayerX) + abs(targetZ - localPlayerZ)) / 2;

			if (distance < localPlayerRange)
			{
				float targetHealth = CHAMPION_LIST[index].Health;
				int targetArmor = CHAMPION_LIST[index].Armor + CHAMPION_LIST[index].BonusArmor;
				if (targetHealth < lowestHealth && targetArmor < lowestArmor && targetHealth > 0)
				{
					lowestHealth = targetHealth;

					lowestIndex = index;
				}
				if (targetHealth < (CHAMPION_LIST[0].BaseAtk + CHAMPION_LIST[0].BonusAtk) * 2)
				{
					lowestIndex = index;
					break;
				}
			}

		}
	}
	return lowestIndex;
}



float GAME_TIME = 0;

float FindGameTime()
{	
	GAME_TIME = Read(LeagueBaseAddress, oGameTime, GAME_TIME);
	return GAME_TIME;
}

bool GAME_STATE = false;

bool GetGameState()
{
	int gameState = 0;
	UINT address = 0;
	address = Read(LeagueBaseAddress, oGameClient, address);
	gameState = Read(address, oGameState, gameState);
	if (gameState == 2)
	{
		GAME_STATE = true;
	}
	else
	{
		GAME_STATE = false;
	}
	return GAME_STATE;
}