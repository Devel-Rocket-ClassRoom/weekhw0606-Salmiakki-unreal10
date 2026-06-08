#pragma once
struct Map {
	int Width = -1;
	int Height = -1;
	int* MapStructure = nullptr;

	Map() = default;
	Map(int x, int y)
	{
		Width = x;
		Height = y;
	}

	~Map()
	{
		if (this->MapStructure)
		{
			delete[] this->MapStructure;
			this->MapStructure = nullptr;
		}
	}

};

static Map* CreateMap()                //맵 정보 동적할당     LeMap, LeMap->MapStructure 메모리 해제 필요
{
	Map* LeMap = new Map(10, 10);
	int* arr = new int[LeMap->Width * (LeMap->Height)]();
	LeMap->MapStructure = arr;
	return LeMap;
}
