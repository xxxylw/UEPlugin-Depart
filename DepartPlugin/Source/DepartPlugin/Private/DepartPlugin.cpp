// Copyright Epic Games, Inc. All Rights Reserved.

#include "DepartPlugin.h"
#include "ContentBrowserModule.h"
#include "EditorAssetLibrary.h"
#include "AssetToolsModule.h"
#include "AssetRegistry/AssetRegistryModule.h"

#include "CustomTabWidget.h"
#include "MyDebugger.h"
#include "CustomStyle.h"

#define LOCTEXT_NAMESPACE "FDepartPluginModule"

namespace Utils
{
	static FString IncrementNameSuffix(const FString& InName)
	{
		FString BaseName = InName;
		int32 Number = 0;

		int32 Index = BaseName.Len() - 1;
		while (Index >= 0 && FChar::IsDigit(BaseName[Index]))
		{
			Index--;
		}

		if (Index < BaseName.Len() - 1)
		{
			FString NumberStr = BaseName.Mid(Index + 1);
			Number = FCString::Atoi(*NumberStr);
			BaseName = BaseName.Left(Index + 1);
		}

		Number++;
		return FString::Printf(TEXT("%s%d"), *BaseName, Number);
	}
}


void FDepartPluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	FCustomStyle::Initialize();
	FCustomStyle::ReloadTextures();
	InitContentBrowserMenuExtension();
	RegistryCustomTab();
}

void FDepartPluginModule::ShutdownModule()
{
#pragma region ForToolBar
	/*
	for ToolBar
	if (UToolMenus::IsToolMenuUIEnabled())
	{
		UToolMenus::UnRegisterStartupCallback(this);
		UToolMenus::UnregisterOwner(this);
	}
	
	*/
#pragma endregion // ForToolBar

	UnRegistryCustomTab();

	FCustomStyle::Shutdown();
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

void FDepartPluginModule::InitContentBrowserMenuExtension()
{
	// Get Module
	FContentBrowserModule& ContentBrowserModule =
		FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
	// Get Menu Extenders
	TArray<FContentBrowserMenuExtender_SelectedPaths>& pathViewContextMenuExtenders = 
		ContentBrowserModule.GetAllPathViewContextMenuExtenders();
	// Add our own menu item
	pathViewContextMenuExtenders.Add(FContentBrowserMenuExtender_SelectedPaths::
		CreateRaw(this, &FDepartPluginModule::CustomContentBrowserMenuExtender));
}

TSharedRef<FExtender> FDepartPluginModule::CustomContentBrowserMenuExtender(const TArray<FString>& SelectedPaths)
{
	TSharedRef<FExtender> fExtender(new FExtender());

	if (SelectedPaths.Num() <= 0)
		return fExtender;

	m_SelectedPaths = SelectedPaths;
	fExtender->AddMenuExtension(
		FName(TEXT("AddToFavorites")),			// hook
		EExtensionHook::After,				// position
		TSharedPtr<FUICommandList>(),		// shortcuts
		FMenuExtensionDelegate::CreateRaw(this, &FDepartPluginModule::CustomMenuExtensionEntry) // delegate
	);

	return fExtender;
}

void FDepartPluginModule::CustomMenuExtensionEntry(FMenuBuilder& fMenuBuilder)
{
	fMenuBuilder.AddMenuEntry(
		FText::FromString(TEXT("Group File")),			// name
		FText::FromString(TEXT("Automatic grouping files in selected folder")), // tip
		FSlateIcon(FCustomStyle::GetStyleSetName(), CustomStyleSetName::Candy),
		FExecuteAction::CreateRaw(this, &FDepartPluginModule::GroupFileImpl)
	);

	fMenuBuilder.AddMenuEntry(
		FText::FromString(TEXT("DepartTab")),			// name
		FText::FromString(TEXT("Its Depart Tab")), // tip
		FSlateIcon(FCustomStyle::GetStyleSetName(), CustomStyleSetName::SantaClaus),
		FExecuteAction::CreateRaw(this, &FDepartPluginModule::OnDepartTabClicked)
	);
}

void FDepartPluginModule::GroupFileImpl()
{
	if (m_SelectedPaths.Num() != 1)
	{
		POPUP_WARN(TEXT("You can only selected 1 folder!"));
		return;
	}

	FAssetToolsModule& AssetToolsModule = 
		FModuleManager::GetModuleChecked<FAssetToolsModule>(TEXT("AssetTools"));
	FAssetRegistryModule& AssetRegistryModule =
		FModuleManager::GetModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));

	TArray<FString> AssetsPaths = UEditorAssetLibrary::ListAssets(m_SelectedPaths[0]);
	TArray<FAssetRenameData> RenameDatas;
	for (auto& AssetPath : AssetsPaths)
	{
		FAssetData AssetData = UEditorAssetLibrary::FindAssetData(AssetPath);
		auto Asset = AssetData.GetAsset();

		FString* FolderPath = m_FolderMap.Find(AssetData.AssetClassPath);

		if (!FolderPath)
		{
			POPUP_WARN(TEXT("[%s] is not support for group"), *AssetData.GetClass()->GetName());
			continue;
		}

		if (!UEditorAssetLibrary::DoesDirectoryExist(*FolderPath))
		{
			UEditorAssetLibrary::MakeDirectory(*FolderPath);
		}

		FString* Prefix = m_PrefixMap.Find(AssetData.AssetClassPath);
		FString NewName, OldName = Asset->GetName();
		if (Prefix)
		{
			if (OldName.StartsWith(*Prefix))
				*Prefix = "";
			if (Asset->IsA<UMaterialInstanceConstant>())
			{
				OldName.RemoveFromEnd("_Inst");
				OldName.RemoveFromStart("M_");
			}
			NewName = *Prefix + OldName;
		}
		else
			NewName = OldName;

		auto MakeObjectPath = [&](const FString& Name)
			{
				return *FolderPath / Name + TEXT(".") + Name;
			};
		FAssetData ExistingAsset =
			AssetRegistryModule.Get().GetAssetByObjectPath(*MakeObjectPath(NewName));

		while (ExistingAsset.IsValid())
		{
			NewName = Utils::IncrementNameSuffix(NewName);
			ExistingAsset =
				AssetRegistryModule.Get().GetAssetByObjectPath(*MakeObjectPath(NewName));
		}

		RenameDatas.Emplace(Asset, *FolderPath, NewName);
	}
	if (RenameDatas.Num() > 0)
	{
		AssetToolsModule.Get().RenameAssets(RenameDatas);
	}
}

void FDepartPluginModule::RegistryCustomTab()
{
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
		FName(TEXT("CustomTab")),
		FOnSpawnTab::CreateRaw(this, &FDepartPluginModule::OnSpawnCustomTab)
	).SetMenuType(ETabSpawnerMenuType::Hidden)
		.SetIcon(FSlateIcon(FCustomStyle::GetStyleSetName(), CustomStyleSetName::Christmas))
		;
}

void FDepartPluginModule::UnRegistryCustomTab()
{
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(
		FName(TEXT("CustomTab"))
	);
}

TSharedRef<SDockTab> FDepartPluginModule::OnSpawnCustomTab(const FSpawnTabArgs& SpawnTabArgs)
{
	TSharedRef<SDockTab> DockTab = 
		SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		.OnTabClosed_Lambda([](TSharedRef<SDockTab> Tab) {
			StaticCastSharedRef<SCunstomTabWidget>(
				Tab->GetContent())->UnBindAssetChangedHandle();
		})
		[
			SNew(SCunstomTabWidget)
			.FolderPath(m_SelectedPaths[0])
		];
	 
	return DockTab;
}

#pragma region ForToolBar
/*
void FDepartPluginModule::RegisterMenus()
{
	UToolMenus::RegisterStartupCallback(
		FSimpleMulticastDelegate::FDelegate::CreateRaw(
			this, &FDepartPluginModule::RegisterToolbarMenu));
}

void FDepartPluginModule::RegisterToolbarMenu()
{
	UToolMenu* ToolbarMenu =
		UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");

	FToolMenuSection& Section =
		ToolbarMenu->FindOrAddSection("Depart");

	Section.AddEntry(
		FToolMenuEntry::InitToolBarButton(
			"DepartPluginToolbarButton",
			FUIAction(FExecuteAction::CreateRaw(
				this, &FDepartPluginModule::OnToolbarButtonClicked)),
			FText::FromString("Depart"),
			FText::FromString("Open Depart Custom Tab"),
			FSlateIcon(
				"EditorStyle",
				"LevelEditor.Tabs.Details"   // ÁÙÊ±Í¼±ê
			)
		)
	);

}
*/
#pragma endregion // ForToolBar

void FDepartPluginModule::OnDepartTabClicked()
{
	if (m_SelectedPaths.Num() != 1)
	{
		POPUP_WARN(TEXT("You slected [%d] folder!(only 1)"), m_SelectedPaths.Num());
		return;
	}

	FGlobalTabmanager::Get()->TryInvokeTab(FName("CustomTab"));
}


#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDepartPluginModule, DepartPlugin)