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

};

