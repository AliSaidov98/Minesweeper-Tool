// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/GameOverWindow.h"

#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION


void SGameOverWindow::Construct(const FArguments& InArgs)
{
	if (GameOverWindow.IsValid()) return;
	
	GameOverWindow = SNew(SWindow)
		.Title(FText::FromString(TEXT("Game Over")))
		.ClientSize(FVector2D(400.0f, 200.0f))
		.IsTopmostWindow(true)
		.SupportsMaximize(false)
		.SupportsMinimize(false)
		.AutoCenter(EAutoCenter::PrimaryWorkArea); 

	GameOverWindow->SetContent(
		SNew(SBorder)
		.Padding(10)
		.BorderImage(FCoreStyle::Get().GetBrush("ToolPanel.GroupBorder"))
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Center)
		[
			SNew(STextBlock)
			.Text(FText::FromString(TEXT("Game Over")))
			.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Bold.ttf"), 32))
			.Justification(ETextJustify::Center)
			.ColorAndOpacity(FLinearColor::Red)
		]
	);
	
	FSlateApplication::Get().AddWindow(GameOverWindow.ToSharedRef());
}


END_SLATE_FUNCTION_BUILD_OPTIMIZATION
