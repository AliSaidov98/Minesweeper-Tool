// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Game/MinesweeperGrid.h"

class MINESWEEPER_TOOL_API SMinesweeperWindow : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMinesweeperWindow)
		{
		}

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:
	void CreateNewGame();
	void OnTileClicked(int32 X, int32 Y);
	void UpdateTileDisplay(int32 X, int32 Y);
	void UpdateAllTiles();

	bool ValidateInput();

	void GameOver();

	TSharedPtr<SGridPanel> GridPanel;
	TArray<TArray<TSharedPtr<STextBlock>>> TileTexts;

	int32 GridWidth = 10;
	int32 GridHeight = 10;
	int32 BombCount = 10;

	int32 GridCellWidth = 30;
	int32 GridCellHeight = 30;

	int32 LabelTextSize = 24;

	FMinesweeperGrid Grid;

	FText GameOverText = FText::FromString("Game Over");
};
