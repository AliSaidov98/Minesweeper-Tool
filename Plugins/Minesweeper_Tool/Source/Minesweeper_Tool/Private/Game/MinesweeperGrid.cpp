// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/MinesweeperGrid.h"
#include "Math/UnrealMathUtility.h"

void FMinesweeperGrid::Initialize(int32 InWidth, int32 InHeight, int32 InBombCount)
{
    Width = InWidth;
    Height = InHeight;
    BombCount = FMath::Clamp(InBombCount, 0, Width * Height);
    bGameOver = false;

    Tiles.Empty();
    
    Tiles.SetNum(Height);
    for (auto& Row : Tiles)
    {
        Row.SetNum(Width);
    }

    PlaceBombs();
    CalculateAdjacents();
}

void FMinesweeperGrid::PlaceBombs()
{
    int32 Placed = 0;
    while (Placed < BombCount)
    {
        int32 X = FMath::RandRange(0, Width - 1);
        int32 Y = FMath::RandRange(0, Height - 1);

        if (!Tiles[Y][X].bIsBomb)
        {
            Tiles[Y][X].bIsBomb = true;
            ++Placed;
        }
    }
}

void FMinesweeperGrid::CalculateAdjacents()
{
    for (int32 Y = 0; Y < Height; ++Y)
    {
        for (int32 X = 0; X < Width; ++X)
        {
            if (Tiles[Y][X].bIsBomb)
                continue;

            int32 Count = 0;
            for (int32 DY = -1; DY <= 1; ++DY)
            {
                for (int32 DX = -1; DX <= 1; ++DX)
                {
                    int32 NX = X + DX;
                    int32 NY = Y + DY;

                    if (IsInBounds(NX, NY) && Tiles[NY][NX].bIsBomb)
                    {
                        ++Count;
                    }
                }
            }
            Tiles[Y][X].AdjacentBombs = Count;
        }
    }
}

bool FMinesweeperGrid::IsInBounds(int32 X, int32 Y) const
{
    return X >= 0 && X < Width && Y >= 0 && Y < Height;
}

void FMinesweeperGrid::Reveal(int32 X, int32 Y)
{
    if (!IsInBounds(X, Y) || Tiles[Y][X].bRevealed)
        return;

    Tiles[Y][X].bRevealed = true;

    if (Tiles[Y][X].bIsBomb)
    {
        GameOverEvent.Broadcast();
        bGameOver = true;
        return;
    }

    if (Tiles[Y][X].AdjacentBombs == 0)
    {
        RevealRecursive(X, Y);
    }
}

void FMinesweeperGrid::RevealRecursive(int32 X, int32 Y)
{
    for (int32 DY = -1; DY <= 1; ++DY)
    {
        for (int32 DX = -1; DX <= 1; ++DX)
        {
            int32 NX = X + DX;
            int32 NY = Y + DY;

            if ((DX != 0 || DY != 0) && IsInBounds(NX, NY) && !Tiles[NY][NX].bRevealed)
            {
                Reveal(NX, NY);
            }
        }
    }
}

const FMinesweeperTile& FMinesweeperGrid::GetTile(int32 X, int32 Y) const
{
    return Tiles[Y][X];
}