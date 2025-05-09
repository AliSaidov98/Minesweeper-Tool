﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class MINESWEEPER_TOOL_API SGameOverWindow : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SGameOverWindow)
		{
		}

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	
	TSharedPtr<SWindow> GameOverWindow;
};
