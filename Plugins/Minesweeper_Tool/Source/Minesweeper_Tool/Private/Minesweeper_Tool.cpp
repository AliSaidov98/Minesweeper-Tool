// Copyright Epic Games, Inc. All Rights Reserved.

#include "Minesweeper_Tool.h"
#include "Minesweeper_ToolStyle.h"
#include "Minesweeper_ToolCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"
#include "Widgets/SMinesweeperWindow.h"

static const FName Minesweeper_ToolTabName("Minesweeper_Tool");

#define LOCTEXT_NAMESPACE "FMinesweeper_ToolModule"

void FMinesweeper_ToolModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FMinesweeper_ToolStyle::Initialize();
	FMinesweeper_ToolStyle::ReloadTextures();

	FMinesweeper_ToolCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FMinesweeper_ToolCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FMinesweeper_ToolModule::PluginButtonClicked),
		FCanExecuteAction());

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner("MinesweeperWindow", FOnSpawnTab::CreateRaw(this, &FMinesweeper_ToolModule::OnCreatePluginTab))
	.SetDisplayName(FText::FromString("Minesweeper"))
	.SetMenuType(ETabSpawnerMenuType::Hidden);
	
	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FMinesweeper_ToolModule::RegisterMenus));
}

void FMinesweeper_ToolModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FMinesweeper_ToolStyle::Shutdown();

	FMinesweeper_ToolCommands::Unregister();
}

void FMinesweeper_ToolModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(
		FName("MinesweeperWindow")
	);
}

void FMinesweeper_ToolModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FMinesweeper_ToolCommands::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("PluginTools");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FMinesweeper_ToolCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

TSharedRef<SDockTab> FMinesweeper_ToolModule::OnCreatePluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SMinesweeperWindow)
		];
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMinesweeper_ToolModule, Minesweeper_Tool)