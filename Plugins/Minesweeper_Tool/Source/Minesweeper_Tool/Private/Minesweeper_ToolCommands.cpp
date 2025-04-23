// Copyright Epic Games, Inc. All Rights Reserved.

#include "Minesweeper_ToolCommands.h"

#define LOCTEXT_NAMESPACE "FMinesweeper_ToolModule"

void FMinesweeper_ToolCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "Minesweeper_Tool", "Execute Minesweeper_Tool action", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
