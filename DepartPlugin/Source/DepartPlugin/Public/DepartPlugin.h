// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"
#include "NiagaraSystem.h"
#include "Materials/MaterialInstanceConstant.h"
#include "WidgetBlueprint.h"

class FDepartPluginModule : public IModuleInterface
{ 
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

#pragma region ContentBrowserMenu
private:
	void InitContentBrowserMenuExtension();
	TSharedRef<FExtender> CustomContentBrowserMenuExtender(const TArray<FString>& SelectedPaths);
	void CustomMenuExtensionEntry(class FMenuBuilder& fMenuBuilder);
	void GroupFileImpl();

private:
	TArray<FString> m_SelectedPaths;
	TMap<FTopLevelAssetPath, FString> m_FolderMap = {
		{	UBlueprint::StaticClass()->GetClassPathName(),					TEXT("/Game/Blueprints")},
		{	UMaterial::StaticClass()->GetClassPathName(),					TEXT("/Game/Materials")},
		{	UMaterialInstanceConstant::StaticClass()->GetClassPathName(),	TEXT("/Game/MaterialInsts")},
		{	UTexture2D::StaticClass()->GetClassPathName(),					TEXT("/Game/Textures/Texture2Ds")},
		{	UStaticMesh::StaticClass()->GetClassPathName(),					TEXT("/Game/StaticMeshs")},
		{	UWorld::StaticClass()->GetClassPathName(),						TEXT("/Game/Levels")},
		{	UNiagaraSystem::StaticClass()->GetClassPathName(),				TEXT("/Game/Niagaras")},
		{	UWidgetBlueprint::StaticClass()->GetClassPathName(),			TEXT("/Game/WidgeBluePrint")},
	};

	TMap<FTopLevelAssetPath, FString> m_PrefixMap =
	{
		{	UBlueprint::StaticClass()->GetClassPathName(),					TEXT("BP_")},
		{	UMaterial::StaticClass()->GetClassPathName(),					TEXT("M_")},
		{	UMaterialInstanceConstant::StaticClass()->GetClassPathName(),	TEXT("MI_")},
		{	UNiagaraSystem::StaticClass()->GetClassPathName(),				TEXT("NS_")},
		{	UStaticMesh::StaticClass()->GetClassPathName(),					TEXT("SM_")},
		{	UTexture2D::StaticClass()->GetClassPathName(),					TEXT("T_")},
		{	UWorld::StaticClass()->GetClassPathName(),						TEXT("L_")},
		{	UWidgetBlueprint::StaticClass()->GetClassPathName(),			TEXT("UB_")},
	};
#pragma endregion // ContentBrowserMenu

#pragma region CunstomTab
private:
	void RegistryCustomTab();
	void UnRegistryCustomTab();
	TSharedRef<SDockTab> OnSpawnCustomTab(const FSpawnTabArgs& SpawnTabArgs);

	void RegisterMenus();
	void RegisterToolbarMenu();
	void OnToolbarButtonClicked();
private:

#pragma endregion // CustomTab
};
