// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

DECLARE_MULTICAST_DELEGATE(FOnGameOver);

struct FMinesweeperTile
{
	bool bIsBomb = false;
	bool bRevealed = false;
	int32 AdjacentBombs = 0;
};

class FMinesweeperGrid
{
public:
	void Initialize(int32 Width, int32 Height, int32 Bombs);
	void Reveal(int32 X, int32 Y);
	const FMinesweeperTile& GetTile(int32 X, int32 Y) const;
	int32 GetWidth() const { return Width; }
	int32 GetHeight() const { return Height; }

	bool IsInBounds(int32 X, int32 Y) const;
	bool IsGameOver() const { return bGameOver; }

	FOnGameOver& OnGameOver() { return GameOverEvent; };

private:
	void PlaceBombs();
	void CalculateAdjacents();
	void RevealRecursive(int32 X, int32 Y);

	int32 Width = 0;
	int32 Height = 0;
	int32 BombCount = 0;
	bool bGameOver = false;

	FOnGameOver GameOverEvent;
	
	TArray<TArray<FMinesweeperTile>> Tiles;
};
