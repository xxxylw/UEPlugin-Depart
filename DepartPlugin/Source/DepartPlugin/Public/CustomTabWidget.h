// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Widgets/SCompoundWidget.h"

#include "NiagaraSystem.h"
#include "Materials/MaterialInstanceConstant.h"
#include "WidgetBlueprint.h"

/**
 * 
 */
class SCunstomTabWidget : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SCunstomTabWidget) {}
		SLATE_ARGUMENT(FString, FolderPath);
	SLATE_END_ARGS();
public:
	void Construct(const FArguments& InArgs);
	
	void UnBindAssetChangedHandle();
private: // Small Fuc
	TSharedRef<SWidget> CreateComboBox();
	TSharedRef<SWidget> CreateListView();
	TSharedRef<SWidget> CreateButtonList();

	TSharedPtr<SHeaderRow> SetupHeaderRow();

	FReply OnInverseButtonClicked();
	FReply OnPrintButtonClicked();
	void OnHeaderRowCheckBoxStateChanged(ECheckBoxState CheckBoxState);
	void OnComboBoxSelectionChanged(TSharedPtr<FString> InSelection, ESelectInfo::Type InSelectInfo);

	void AddSelectedAsset(const TSharedPtr<FAssetData> AssetData);
	void RemoveSelectedAsset(const TSharedPtr<FAssetData> AssetData);
	bool isAssetBeSelected(const TSharedPtr<FAssetData> AssetData);

	TSharedPtr<SWidget> OnListViewMenuOpening();
	void OnFindBtnClicked();
	void OnDeleteBtnClicked();

	void FilterAssets();
	void GetAssetsInFolderPath();

private:
	FString m_FolderPath;
	TArray<TSharedPtr<FString>>		m_ComboboxSrcOpts;
	TArray<TSharedPtr<FAssetData>>	m_AssetsInFolderPath;
	TArray<TSharedPtr<FAssetData>>	m_SelectedAssets;
	TArray<TSharedPtr<FAssetData>>	m_FilteredAssets;
	FTopLevelAssetPath* m_FilterType;

	TSharedPtr<STextBlock> m_ComboBoxText;
	TSharedPtr<SListView<TSharedPtr<FAssetData>>> m_ListView;

	FDelegateHandle m_AssetAddedHandle;
	FDelegateHandle m_AssetRemovedHandle;

	TMap<TSharedPtr<FString>, FTopLevelAssetPath> m_ComboboxFilterMap = {
		{MakeShared<FString>(TEXT("All")),					nullptr },
		{MakeShared<FString>(TEXT("BluePrint")),			UBlueprint::StaticClass()->GetClassPathName()},
		{MakeShared<FString>(TEXT("Texture2D")),			UTexture2D::StaticClass()->GetClassPathName()},
		{MakeShared<FString>(TEXT("StaticMesh")),			UStaticMesh::StaticClass()->GetClassPathName()},
		{MakeShared<FString>(TEXT("Material")),				UMaterial::StaticClass()->GetClassPathName()},
		{MakeShared<FString>(TEXT("MaterialInstace")),		UMaterialInstanceConstant::StaticClass()->GetClassPathName()},
		{MakeShared<FString>(TEXT("Level")),				UWorld::StaticClass()->GetClassPathName()},
		{MakeShared<FString>(TEXT("NigaraSystem")),			UNiagaraSystem::StaticClass()->GetClassPathName()},
	};

	friend class SCustomTableRow;
};