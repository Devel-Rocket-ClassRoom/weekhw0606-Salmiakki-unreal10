// NewProject_Base_Cpp.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "Map.h"
#include "Position.h"
#include "Ship.h"
#include "Utils.h"
using namespace std;

Map* CreateMap()
{
    Map* LeMap = new Map(10, 10);
    int* arr = new int[LeMap->Width * (LeMap->Height)]();
    LeMap->MapStructure = arr;
    return LeMap;
}

Ship** SpawnShips(Map& map)
{

    Ship** EnemyFleet = new Ship * [4];
    EnemyFleet[0] = new Ship(DD, rand() % 2);
    EnemyFleet[1] = new Ship(CC, rand() % 2); 
    EnemyFleet[2] = new Ship(BB, rand() % 2);
    EnemyFleet[3] = new Ship(CV, rand() % 2);

   
    for (int k = 0; k < ShipTypeCount; k++)
    {
        Ship* eachShip = EnemyFleet[k];
        Position newPos = Position(rand() % (map.Width), rand() % (map.Height));
        Position tempPos = newPos;
        bool hasSucceded = false;
        //printf("%d ", eachShip->GetSize());
        
        if (eachShip->GetHorizontal())
        {
            //생성 가능 체크

            while(!hasSucceded)
            {
                hasSucceded = true;
                for (int i = 0; i < eachShip->GetSize(); i++)
                {
                    if (newPos.X + i >= map.Width || map.MapStructure[(newPos.Y) * map.Width + newPos.X+i] != 0)
                    {
                        hasSucceded = false;
                        newPos = Position(rand() % (map.Width), rand() % (map.Height));
                        tempPos = newPos;
                        break;
                    }
                }
            }    //가로 생성
            for (int j = 0; j < eachShip->GetSize(); j++)
            {   
                eachShip->SetPos(tempPos, j);
                map.MapStructure[eachShip->GetPos()[j].Y * map.Width + eachShip->GetPos()[j].X] = eachShip->GetSize();
                tempPos = tempPos + Position(1, 0);
            }
        }
        else
        {
            while (!hasSucceded)
            {
                hasSucceded = true;
                for (int i = 0; i < eachShip->GetSize(); i++)
                {
                    if (newPos.Y + i >= map.Height || map.MapStructure[(newPos.Y+i) * map.Width + newPos.X] != 0)
                    {
                        hasSucceded = false;
                        newPos = Position(rand() % (map.Width), rand() % (map.Height));
                        tempPos = newPos;
                        break;
                    }
                }
            }
                //세로 생성
            for (int j = 0; j < eachShip->GetSize(); j++)
            {
                eachShip->SetPos(tempPos, j);
                map.MapStructure[eachShip->GetPos()[j].Y * map.Width + eachShip->GetPos()[j].X] = eachShip->GetSize();
                tempPos = tempPos + Position(0, 1);
            }


        }
        //delete eachShip;
    }
	return EnemyFleet;
    

}

void PrintWorld(const Map* Maze, bool reveal=false)
{
    for (int i = -2; i < (Maze->Height); i++)
    {
        printf("%s |", i>-1? to_string(i).c_str() : " ");
        for (int j = 0; j < (Maze->Width); j++)
        {
            if(i >-1)
            {
                if (Maze->MapStructure[i * Maze->Width + j] == 0)
                {
                    printf(". ");
                }
                else if (Maze->MapStructure[i * Maze->Width + j] == -1)
                {
                    printf("X ");
                }
                else if (Maze->MapStructure[i * Maze->Width + j] == -2)
                {
                    printf("O ");
                }
                else
                {
                    printf("%s ", reveal ? to_string(Maze->MapStructure[i * Maze->Width + j]).c_str() : ".");
                }
            }
            else
            {
                string kara = i==-1?"-": to_string(j) ;
				printf("%s ", kara.c_str());
            }
        }
        printf("\n");
    }
}



int main()
{
    srand(time(0));
	int AvilableAttacks = 30;
	int RemainingShips = ShipTypeCount;
    Map* Ocean = CreateMap();
    Ship** EnemyFleet = SpawnShips(*Ocean);
    int index = -1;
    while (AvilableAttacks > 0)
    {
        system("cls");
        int x, y;
        PrintWorld(Ocean);
        cout << "남은 공격 횟수: " << AvilableAttacks << " | 남은 적 함선 수: " << RemainingShips << endl;
        do
        {
        cout << "공격할 좌표를 입력하세요 (x y): ";
            cin >> x >> y;
        } while (x < 0 || x >= Ocean->Width || y < 0 || y >= Ocean->Height || Ocean->MapStructure[y * (*Ocean).Width + x]<0);

        if (Ocean->MapStructure[y * (*Ocean).Width + x] == 0)
        {
            printf("공격이 빗나갔습니다!\n");
            Ocean->MapStructure[y * Ocean->Width + x] = -1;
        }
        else
        {
            cout << "명중!\n";
            index = (Ocean->MapStructure[y * (*Ocean).Width + x] - 2);
            //delete EnemyFleet[index];
            if (index > -1)
            {
                EnemyFleet[index]->TakeDamage();
                if (EnemyFleet[index]->GetisDead())
                {
                    RemainingShips--;
                    
                }
            }
            if (RemainingShips == 0)
            {
                cout << "모든 적 함선을 격침시켰습니다! 승리!" << endl;
                break;
			}
            Ocean->MapStructure[y * Ocean->Width + x] = -2;
           
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
        AvilableAttacks--;
       
        /*cin.ignore();
        cin.get();*/
    }
	system("cls");
    PrintWorld(Ocean, true);
	cout << "게임 오버" << endl;
    for (int i = 0; i < ShipTypeCount; i++)
    {
        delete[] EnemyFleet[i];
        EnemyFleet[i] = nullptr;
	}
    delete[] Ocean->MapStructure;
    Ocean->MapStructure = nullptr;
    delete Ocean;
    Ocean = nullptr;
}

