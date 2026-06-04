#pragma once
#include "Ship.h"
#include "Position.h"

enum ShipType
{
	DD = 2,
	CC = 3,
	BB = 4,
	CV = 5
};

class Ship
{
	int Size = 0;
	Position* Pos = {};
	bool Horizontal = true;
public:
	Ship(ShipType whatship, bool ishorizontal = true)
	{
		Size = whatship;
		Horizontal = ishorizontal;
		Pos = new Position[Size];
	}
	bool GetHorizontal()
	{
		return Horizontal;
	}
	int GetSize()
	{
		return Size;
	}
	void SetPos(Position itspos, int index=0)
	{
		Pos[index] = itspos;
	}
	Position* GetPos()
	{
		return Pos;
	}
};