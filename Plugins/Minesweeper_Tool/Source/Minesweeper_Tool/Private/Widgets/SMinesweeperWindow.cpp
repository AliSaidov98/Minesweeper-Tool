// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/SMinesweeperWindow.h"
#include "Validation/ValidationInput.h"
#include "Widgets/GameOverWindow.h"
#include "Widgets/Input/SNumericEntryBox.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SMinesweeperWindow::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SNew(SVerticalBox)

        + SVerticalBox::Slot()
        .AutoHeight()
        .Padding(2)
        [

            SNew(SVerticalBox)
#pragma region  Width
            + SVerticalBox::Slot()
            .AutoHeight()
            [
                SNew(SHorizontalBox)

                + SHorizontalBox::Slot().AutoWidth().Padding(10)
                [
                    SNew(STextBlock).Text(FText::FromString("Width"))
                    .Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Bold.ttf"), LabelTextSize))
                ]
                + SHorizontalBox::Slot().AutoWidth().Padding(2)
                [
                    SNew(SNumericEntryBox<int32>)
                    .Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Bold.ttf"), LabelTextSize))
                    .Value_Lambda([this]() { return GridWidth; })
                    .OnValueChanged_Lambda([this](int32 NewValue) { GridWidth = NewValue; })
                    .MinValue(1)
                ]
            ]
#pragma endregion
            
#pragma region  Height
            + SVerticalBox::Slot()
            .AutoHeight()
            [
                SNew(SHorizontalBox)
                
                + SHorizontalBox::Slot().AutoWidth().Padding(10)
                [
                    SNew(STextBlock).Text(FText::FromString("Height"))
                    .Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Bold.ttf"), LabelTextSize))
                ]
                + SHorizontalBox::Slot().AutoWidth().Padding(2)
                [
                    SNew(SNumericEntryBox<int32>)
                    .Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Bold.ttf"), LabelTextSize))
                    .Value_Lambda([this]() { return GridHeight; })
                    .OnValueChanged_Lambda([this](int32 NewValue) { GridHeight = NewValue; })
                    .MinValue(1)
                ]
            ]
#pragma endregion
            
#pragma region  Bombs
            + SVerticalBox::Slot()
            .AutoHeight()
            [
                SNew(SHorizontalBox)
                + SHorizontalBox::Slot().AutoWidth().Padding(10)
                [
                    SNew(STextBlock).Text(FText::FromString("Bombs"))
                    .Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Bold.ttf"), LabelTextSize))
                ]
                + SHorizontalBox::Slot().AutoWidth().Padding(2)
                [
                    SNew(SNumericEntryBox<int32>)
                    .Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Bold.ttf"), LabelTextSize))
                    .Value_Lambda([this]() { return BombCount; })
                    .OnValueChanged_Lambda([this](int32 NewValue) { BombCount = NewValue; })
                    .MinValue(0)
                ]
            ]
#pragma endregion
            
#pragma region  New Game
            + SVerticalBox::Slot()
            .AutoHeight()
            [
                SNew(SHorizontalBox)
                + SHorizontalBox::Slot().AutoWidth().Padding(2)
                [
                    SNew(SButton)
                    .OnClicked_Lambda([this]() -> FReply
                    {
                        CreateNewGame();
                        return FReply::Handled();
                    })
                    [
                        SNew(SBox)
                        .VAlign(VAlign_Center)
                        .HAlign(HAlign_Center)  
                        [
                            SNew(STextBlock)
                            .Text(FText::FromString(" New Game "))
                            .Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Bold.ttf"), LabelTextSize))
                            .Justification(ETextJustify::Center)
                        ]
                    ]
                ]
            ]
            
#pragma endregion
            
        ]

        + SVerticalBox::Slot()
        .AutoHeight()
        .Padding(4)
        [
            SAssignNew(GridPanel, SGridPanel)       
        ]
	];
    
    CreateNewGame();
    
    Grid.OnGameOver().AddSP(SharedThis(this), &SMinesweeperWindow::GameOver);
}

void SMinesweeperWindow::CreateNewGame()
{
    if (!ValidateInput())
    {
        return;
    }
    
    GridPanel->ClearChildren();
    Grid.Initialize(GridWidth, GridHeight, BombCount);
    
    TileTexts.Empty();
    TileTexts.SetNum(GridHeight);

    for (int32 Y = 0; Y < GridHeight; ++Y)
    {
        TileTexts[Y].SetNum(GridWidth);
        
        for (int32 X = 0; X < GridWidth; ++X)
        {
            TSharedPtr<STextBlock> TextBlock;

            GridPanel->AddSlot(X, Y)
            [
                SNew(SButton)
                .OnClicked_Lambda([this, X, Y]() -> FReply
                {
                    OnTileClicked(X, Y);
                    return FReply::Handled();
                })
                [
                    SNew(SBox)
                    .VAlign(VAlign_Center)
                    .WidthOverride(GridCellWidth)
                    .HeightOverride(GridCellHeight)
                    .HAlign(HAlign_Center)  
                    [
                        SAssignNew(TextBlock, STextBlock)
                        .Text(FText::FromString(" "))
                        .Justification(ETextJustify::Center)
                    ]
                ]
            ];

            TileTexts[Y][X] = TextBlock;
        }
    }

    UpdateAllTiles();
}

void SMinesweeperWindow::OnTileClicked(int32 X, int32 Y)
{
    if (Grid.IsGameOver())
        return;

    Grid.Reveal(X, Y);
    UpdateAllTiles();
}

void SMinesweeperWindow::UpdateTileDisplay(int32 X, int32 Y)
{
    const auto& Tile = Grid.GetTile(X, Y);
    const auto& TextBlock = TileTexts[Y][X];

    if (Tile.bRevealed)
    {
        if (Tile.bIsBomb)
        {
            TextBlock->SetText(FText::FromString(" X "));
        }
        else if (Tile.AdjacentBombs > 0)
        {
            TextBlock->SetText(FText::AsNumber(Tile.AdjacentBombs));
        }
        else
        {
            TextBlock->SetText(FText::FromString(" "));
        }
    }
    else
    {
        TextBlock->SetText(FText::FromString(" ? "));
    }
}

void SMinesweeperWindow::UpdateAllTiles()
{
    for (int32 Y = 0; Y < Grid.GetHeight(); ++Y)
    {
        for (int32 X = 0; X < Grid.GetWidth(); ++X)
        {
            UpdateTileDisplay(X, Y);
        }
    }
}

bool SMinesweeperWindow::ValidateInput()
{
    const TArray<FValidationRule> Rules = ValidationInput::CreateInputRules(GridWidth, GridHeight, BombCount);

    for (const FValidationRule& Rule : Rules)
    {
        if (!Rule.bIsValid)
        {
            FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(Rule.ErrorMessage));
            return false;
        }
    }
    
    return true;
}

void SMinesweeperWindow::GameOver()
{
    TSharedPtr<SGameOverWindow> GameOverWindow = SNew(SGameOverWindow);
    GameOverWindow->Construct(SGameOverWindow::FArguments());
}


END_SLATE_FUNCTION_BUILD_OPTIMIZATION
