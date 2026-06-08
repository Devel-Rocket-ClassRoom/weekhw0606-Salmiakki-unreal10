#pragma once
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "Utils.h"
#include "Position.h"
#include "Map.h"
#include "Ship.h"
#include "BattleShip.h"
using namespace std;

void BattleShip::SpawnShips(Map& map, Ship** EnemyFleet)
{
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

            while (!hasSucceded)
            {
                hasSucceded = true;
                for (int i = 0; i < eachShip->GetSize(); i++)
                {
                    if (newPos.X + i >= map.Width || map.MapStructure[(newPos.Y) * map.Width + newPos.X + i] != 0)
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
                    if (newPos.Y + i >= map.Height || map.MapStructure[(newPos.Y + i) * map.Width + newPos.X] != 0)
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
    //return EnemyFleet;


}

void BattleShip::PrintWorld(const Map* Maze, bool reveal)
{
    for (int i = -2; i < (Maze->Height); i++)
    {
        printf("%s |", i > -1 ? to_string(i).c_str() : " ");
        for (int j = 0; j < (Maze->Width); j++)
        {
            if (i > -1)
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
                std::string kara = i == -1 ? "-" : to_string(j);
                printf("%s ", kara.c_str());
            }
        }
        printf("\n");
    }
}

void BattleShip::GameLoop(int& AvilableAttacks, int& RemainingShips, Map* Ocean, Ship** EnemyFleet)
{
    while (AvilableAttacks > 0)
    {
        int index = -1;
        system("cls");
        int x, y;
        PrintWorld(Ocean);
        cout << "남은 공격 횟수: " << AvilableAttacks << " | 남은 적 함선 수: " << RemainingShips << endl;
        do
        {
            cout << "공격할 좌표를 입력하세요 (x y): ";
            cin >> x >> y;
        } while (x < 0 || x >= Ocean->Width || y < 0 || y >= Ocean->Height || Ocean->MapStructure[y * (*Ocean).Width + x] < 0);

        if (Ocean->MapStructure[y * (*Ocean).Width + x] == 0)
        {
            printf("공격이 빗나갔습니다!\n");
            Ocean->MapStructure[y * Ocean->Width + x] = -1;
        }
        else
        {
            cout << "명중!\n";
            index = (Ocean->MapStructure[y * (*Ocean).Width + x] - 2);
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

    }
}

void BattleShip::FinishGameNShowResult(Map* Ocean)
{
    system("cls");
    PrintWorld(Ocean, true);
    cout << "게임 오버" << endl;
}

void BattleShip::ClearData()
{
    if (EnemyFleet)
    {
        for (int i = 0; i < ShipTypeCount; i++)
        {
            
            delete EnemyFleet[i];
            EnemyFleet[i] = nullptr;
        }
        delete[] EnemyFleet;
        EnemyFleet = nullptr;
    }
    if (Ocean)
    {
        delete Ocean;
        Ocean = nullptr;
    }
}


