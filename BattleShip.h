#pragma once
#include "Map.h"
#include "Ship.h"
Map* CreateMap();

Ship** SpawnShips(Map& map);

void PrintWorld(const Map* Maze, bool reveal);

void Homework01_Run();
