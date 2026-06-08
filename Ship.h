#pragma once
#include <string>
#include "Position.h"

enum ShipType
{
	DD = 2,
	CC = 3,
	BB = 4,
	CV = 5,
	ShipTypeCount = 4
};
std::string ShipName[] = { "구축함", "순양함", "전함", "항공모함" };


class Ship
{
	int Size = 0;
	int HP = 0;
	Position* Pos = {};
	bool Horizontal = true;
	bool isDead = false;
public:
	Ship(ShipType whatship, bool ishorizontal = true)
	{
		Size = whatship;
		HP = (int)Size;
		Horizontal = ishorizontal;
		Pos = new Position[Size];
	}

	inline bool GetHorizontal()
	{
		return Horizontal;
	}
	inline int GetSize()
	{
		return Size;
	}
	inline void SetPos(Position itspos, int index=0)
	{
		Pos[index] = itspos;
	}
	inline Position* GetPos()
	{
		return Pos;
	}
	void TakeDamage()
	{
		HP--;
		if (HP <= 0)
		{
			Die();
		}
	}
	void Die()
	{
		isDead = true;
		printf("***%s이 격침되었습니다!***\n", ShipName[Size-2].c_str());
	}
	inline bool GetisDead()
	{
		return isDead;
	}
};

Ship** CreateFleet()            //함대 동적할당        EnemyFleet 메모리 해제 필요
{
	Ship** EnemyFleet = new Ship * [ShipTypeCount];
	for (int i = 0; i < ShipTypeCount; i++)
	{
		EnemyFleet[i] = new Ship((ShipType)(DD+i), rand() % 2);
	}
	return EnemyFleet;
}