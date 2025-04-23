// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
struct FValidationRule
{
	bool bIsValid;
	FString ErrorMessage;

	FValidationRule(bool bCondition, const FString& InMessage)
		: bIsValid(bCondition), ErrorMessage(InMessage) {}
};

namespace  ValidationInput
{
	inline TArray<FValidationRule> CreateInputRules(int32 GridWidth, int32 GridHeight, int32 BombCount)
	{
		const int32 MaxBombs = GridWidth * GridHeight;

		return {
				{ GridWidth > 0, TEXT("Grid Width cannot be zero or negative.\nPlease enter a valid number.") },
				{ GridHeight > 0, TEXT("Grid Height cannot be zero or negative.\nPlease enter a valid number.") },
				{ BombCount > 0, TEXT("The number of bombs cannot be zero or negative.\nPlease enter a valid number.") },
				{ BombCount <= MaxBombs, TEXT("The number of bombs cannot be greater than the number of cells on the grid.\nPlease enter a valid number.") }
		};
	}
};
