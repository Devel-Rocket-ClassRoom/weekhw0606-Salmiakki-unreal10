#pragma once
struct Position
{
	int X = 0;
	int Y = 0;


	Position()
	{
	}

	Position(int x, int y)
	{
		X = x;
		Y = y;
	}

	Position operator+(const Position& InOther)	const
	{
		Position Result;
		Result.X = this->X + InOther.X;
		Result.Y = this->Y + InOther.Y;


		return Result;
	}
	Position operator-(const Position& InOther)	const
	{
		Position Result;
		Result.X = this->X - InOther.X;
		Result.Y = this->Y - InOther.Y;


		return Result;
	}
};