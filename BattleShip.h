#pragma once
#include "Map.h"
#include "Ship.h"
Map* CreateMap();

Ship** CreateFleet();
using namespace std;

class BattleShip
{
	int AvilableAttacks = 0;
	int RemainingShips = 0;
	Map* Ocean = nullptr;
	Ship** EnemyFleet = nullptr;
public:
	BattleShip()
	{
		AvilableAttacks = 3;
		RemainingShips = ShipTypeCount;
		Ocean = CreateMap();
		EnemyFleet = CreateFleet();

		SpawnShips(*Ocean, EnemyFleet);
		GameLoop(AvilableAttacks, RemainingShips, Ocean, EnemyFleet);
		FinishGameNShowResult(Ocean);
        //ClearData();
	}	


	void SpawnShips(Map& map, Ship** EnemyFleet);
	void PrintWorld(const Map* Maze, bool reveal = false);
	void GameLoop(int& AvilableAttacks, int& RemainingShips, Map* Ocean, Ship** EnemyFleet);
	void FinishGameNShowResult(Map* Ocean);
    void ClearData();
};


//~BattleShip()
//{
//	if (EnemyFleet)
//	{
//		for (int i = 0; i < ShipTypeCount; i++)
//		{
//			delete[] EnemyFleet[i];
//			EnemyFleet[i] = nullptr;
//		}
//		delete EnemyFleet;
//		EnemyFleet = nullptr;
//	}
//	if (Ocean)
//	{
//		delete Ocean;
//		Ocean = nullptr;
//	}
//}