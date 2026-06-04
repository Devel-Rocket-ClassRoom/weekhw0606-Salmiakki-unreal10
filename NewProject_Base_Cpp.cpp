// NewProject_Base_Cpp.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include "Map.h"
#include "Position.h"
#include "Ship.h"
#include "Utils.h"


Map* CreateMap()
{
    Map* LeMap = new Map(10, 10);
    int* arr = new int[LeMap->Width * (LeMap->Height)];
    for (int i = 0; i < LeMap->Height; i++)
    {
        for (int j = 0; j < LeMap->Width; j++)
        {
            arr[i * LeMap->Width + j] = 0;
        }
    }
    LeMap->MapStructure = arr;
    return LeMap;
}

void SpawnShips(Map& map)
{
    srand(time(0));
    Ship* EnemyFleet[4] = { new Ship(DD),  new Ship(CC) , new Ship(BB) , new Ship(CV)};
   
    for (Ship* eachShip : EnemyFleet)
    {
        //printf("%d ", eachShip->GetSize());
        
        if (eachShip->GetHorizontal())
        {
            //int randomY = GetRandomRange(0, map.Height-1);
            //int randomX = GetRandomRange(0, map.Width-1);

            bool hasSucceded = false;
            Position randomPos = Position(rand() % (map.Width - 1), rand() % (map.Height - 1));
            Position newPos = randomPos;
            Position tempPos = newPos;
            //생성 가능 체크

            while(hasSucceded = true)
            {
                for (int i = 0; i < eachShip->GetSize(); i++)
                {
                    if (map.MapStructure[newPos.Y * map.Width + newPos.X+i] == 0 && map.Width > newPos.X + i)
                    {
                        hasSucceded = true;
                    }
                    else
                    {
                        hasSucceded = false;
                        newPos = Position(rand() % (map.Width - 1), rand() % (map.Height - 1));
                        tempPos = newPos;
                    }        
                }
                break;
            }
            for (int j = 0; j < eachShip->GetSize(); j++)
            {   
                eachShip->SetPos(tempPos, j);
                tempPos = tempPos + Position(1, 0);
            }

            for (int l = 0; l < eachShip->GetSize(); l++)
            {
                Position ShipPartPos = eachShip->GetPos()[l];
                map.MapStructure[ShipPartPos.Y * map.Width + ShipPartPos.X] = eachShip->GetSize();
            }


        }
        else
        {
        //세로 생성

        }
        //map.MapStructure
    }
    //printf("\n");
   // printf("%d ", rand() % (map.Width - 1));

}

void PrintWorld(const Map* Maze)
{
    for (int i = 0; i < (Maze->Height); i++)
    {
        for (int j = 0; j < (Maze->Width); j++)
        {
            if (Maze->MapStructure[i * Maze->Width + j] == 0)
            {
                printf(". ");
            }
            else
            {
                printf("%d ", Maze->MapStructure[i * Maze->Width + j]);
            }
        }
        printf("\n");
    }
}

int main()
{
    Map* Ocean = CreateMap();
    /*for (int i = 0; i <100; i++)
    {
        printf("%d ", (Ocean->MapStructure)[i]);
    }*/
    SpawnShips(*Ocean);
    PrintWorld(Ocean);
    delete Ocean->MapStructure;
    Ocean->MapStructure = nullptr;
    delete Ocean;
    Ocean = nullptr;
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
