// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Framework/Commands/Commands.h"
#include "Minesweeper_ToolStyle.h"

class FMinesweeper_ToolCommands : public TCommands<FMinesweeper_ToolCommands>
{
public:

	FMinesweeper_ToolCommands()
		: TCommands<FMinesweeper_ToolCommands>(TEXT("Minesweeper_Tool"), NSLOCTEXT("Contexts", "Minesweeper_Tool", "Minesweeper_Tool Plugin"), NAME_None, FMinesweeper_ToolStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
