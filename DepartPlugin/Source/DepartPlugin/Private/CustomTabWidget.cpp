// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomTabWidget.h"
#include "CustomTableRow.h"
#include "MyDebugger.h"

#include "EditorAssetLibrary.h"
#include "ObjectTools.h"
#include "AssetRegistry/AssetRegistryModule.h"

void SCunstomTabWidget::Construct(const FArguments& InArgs)
{	
	m_FolderPath = InArgs._FolderPath;

	m_ComboboxFilterMap.GetKeys(m_ComboboxSrcOpts);

	GetAssetsInFolderPath();
	m_FilteredAssets = m_AssetsInFolderPath;

	FAssetRegistryModule& AssetRegistryModule =
		FModuleManager::LoadModuleChecked<FAssetRegistryModule>(FName("AssetRegistry"));
	m_AssetAddedHandle = AssetRegistryModule.Get().OnAssetAdded().AddLambda([this](const FAssetData& AssetData) {
			GetAssetsInFolderPath();
			FilterAssets();
			UEditorAssetLibrary::SaveAsset(AssetData.GetObjectPathString());
		});
	m_AssetRemovedHandle = AssetRegistryModule.Get().OnAssetRemoved().AddLambda([this](const FAssetData& AssetData) {
			UEditorAssetLibrary::SaveAsset(AssetData.GetObjectPathString());
			GetAssetsInFolderPath();
			FilterAssets();
		});

	ChildSlot
	[
		SNew(SVerticalBox)
		+SVerticalBox::Slot()
		.AutoHeight()
		.Padding(5.5)
		[
			CreateComboBox()
		]

		+ SVerticalBox::Slot()
		.VAlign(VAlign_Fill)
		[
			CreateListView()
		]

		+ SVerticalBox::Slot()
		.AutoHeight()
		.HAlign(HAlign_Right)
		.Padding(5.5)
		[
			CreateButtonList()
		]
	];
}

void SCunstomTabWidget::UnBindAssetChangedHandle()
{
	FAssetRegistryModule& AssetRegistryModule =
		FModuleManager::LoadModuleChecked<FAssetRegistryModule>(FName("AssetRegistry"));
	AssetRegistryModule.Get().OnAssetAdded().Remove(m_AssetAddedHandle);
	AssetRegistryModule.Get().OnAssetRemoved().Remove(m_AssetRemovedHandle);
}

TSharedRef<SWidget> SCunstomTabWidget::CreateComboBox()
{
	TSharedRef<SWidget> CustomComboBox =
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.Padding(5.5)
		.VAlign(VAlign_Center)
		[
			SNew(STextBlock)
			.Text(FText::FromString(TEXT("Filter Type : ")))
		]

		+ SHorizontalBox::Slot()
		.MaxWidth(200)
		.Padding(5.5)
		.VAlign(VAlign_Center)
		[
			SNew(SComboBox<TSharedPtr<FString>>)
				.OptionsSource(&m_ComboboxSrcOpts)
				.OnGenerateWidget_Lambda([](TSharedPtr<FString> Item)
					{
						return SNew(STextBlock).Text(FText::FromString(*Item));
					}
				)
				.OnSelectionChanged(this, &SCunstomTabWidget::OnComboBoxSelectionChanged)
				[
					SAssignNew(m_ComboBoxText, STextBlock)
					.Text(FText::FromString(TEXT("All")))
				]
		]

		+ SHorizontalBox::Slot()
		.AutoWidth()
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Right)
		.Padding(5.5)
		.AutoWidth()
		[
			SNew(SButton)
				.Text(FText::FromString(TEXT("Invert")))
				.OnClicked(this, &SCunstomTabWidget::OnInverseButtonClicked)
		]
		;
	return CustomComboBox;
}

TSharedRef<SWidget> SCunstomTabWidget::CreateListView()
{
		SAssignNew(m_ListView, SListView<TSharedPtr<FAssetData>>)
		.ListItemsSource(&m_FilteredAssets)
		.OnGenerateRow_Lambda([this](TSharedPtr<FAssetData> Item, const TSharedRef<STableViewBase>& OwnerTable)
			{
				return
					SNew(SCustomTableRow, OwnerTable)
					.AssetData(Item)
					.OwnerWidget(SharedThis(this))
					;
			})
		.HeaderRow(SetupHeaderRow())
		.OnContextMenuOpening(this, &SCunstomTabWidget::OnListViewMenuOpening)
		;

	return m_ListView.ToSharedRef();
}

TSharedRef<SWidget> SCunstomTabWidget::CreateButtonList()
{
	TSharedRef<SWidget> ButtonList =
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.VAlign(VAlign_Center)
		.Padding(5.5)
		.AutoWidth()
		[
			SNew(SButton)
			.Text(FText::FromString(TEXT("Print")))
			.OnClicked(this, &SCunstomTabWidget::OnPrintButtonClicked)
		]
	;
	return ButtonList;
}

TSharedPtr<SHeaderRow> SCunstomTabWidget::SetupHeaderRow()
{
	TSharedPtr<SHeaderRow> CustomHeaderRow = 
		SNew(SHeaderRow)
		+ SHeaderRow::Column(CustomTabColumns::Selected)
		.DefaultLabel(FText::FromString(CustomTabColumns::Selected.ToString()))
		.HAlignHeader(HAlign_Left)
		.FixedWidth(26)
		.HAlignCell(HAlign_Center)
		[
			SNew(SCheckBox)
			.OnCheckStateChanged(this, &SCunstomTabWidget::OnHeaderRowCheckBoxStateChanged)
			.IsChecked_Lambda([&]() {
				if (m_SelectedAssets.Num() == 0)
					return ECheckBoxState::Unchecked;
				return m_SelectedAssets.Num() == m_FilteredAssets.Num() ? ECheckBoxState::Checked
					: ECheckBoxState::Undetermined;
			})
		]
		
		+ SHeaderRow::Column(CustomTabColumns::Asset)
		.DefaultLabel(FText::FromString(CustomTabColumns::Asset.ToString()))
		.FillWidth(3)

		+ SHeaderRow::Column(CustomTabColumns::Class)
		.DefaultLabel(FText::FromString(CustomTabColumns::Class.ToString()))
		.FillWidth(3)

		+ SHeaderRow::Column(CustomTabColumns::Referencers)
		.DefaultLabel(FText::FromString(CustomTabColumns::Referencers.ToString()))
		.FillWidth(3)
		;

	return CustomHeaderRow;
}

FReply SCunstomTabWidget::OnInverseButtonClicked()
{
	TArray<TSharedPtr<FAssetData>>	Temp;
	for (auto& AssetData : m_FilteredAssets)
	{
		if (!m_SelectedAssets.Contains(AssetData))
		{
			Temp.Add(AssetData);
		}
	}
	m_SelectedAssets = Temp;
	return FReply::Handled();
}

FReply SCunstomTabWidget::OnPrintButtonClicked()
{
	for (auto& SelectedAsset : m_SelectedAssets)
	{
		SCREEN_LOG(SelectedAsset->GetAsset()->GetName());
		LOG_LOG(TEXT("%s"), *SelectedAsset->GetAsset()->GetName());
	}
	return FReply::Handled();
}

void SCunstomTabWidget::OnHeaderRowCheckBoxStateChanged(ECheckBoxState CheckBoxState)
{
	switch (CheckBoxState)
	{
	case ECheckBoxState::Unchecked:
		m_SelectedAssets.Empty();
		break;
	case ECheckBoxState::Checked:
		m_SelectedAssets = m_FilteredAssets;
		break;
	default:
		break;
	}
}

void SCunstomTabWidget::OnComboBoxSelectionChanged(TSharedPtr<FString> InSelection, ESelectInfo::Type InSelectInfo)
{
	m_ComboBoxText->SetText(FText::FromString(*InSelection));
	
	m_FilterType = m_ComboboxFilterMap.Find(InSelection);
	if (!m_FilterType)
	{
		m_FilteredAssets = m_AssetsInFolderPath;
		return;
	}
	
	FilterAssets();
}

void SCunstomTabWidget::AddSelectedAsset(const TSharedPtr<FAssetData> AssetData)
{
	m_SelectedAssets.AddUnique(AssetData);
}

void SCunstomTabWidget::RemoveSelectedAsset(const TSharedPtr<FAssetData> AssetData)
{
	m_SelectedAssets.Remove(AssetData);
}

bool SCunstomTabWidget::isAssetBeSelected(const TSharedPtr<FAssetData> AssetData)
{
	return m_SelectedAssets.Contains(AssetData);
}

TSharedPtr<SWidget> SCunstomTabWidget::OnListViewMenuOpening()
{
	FMenuBuilder MenuBuilder(
		true,
		TSharedPtr<FUICommandList>()
	);

	MenuBuilder.AddMenuEntry(
		FText::FromString(TEXT("Find")),
		FText::FromString(TEXT("Find selected asset")),
		FSlateIcon(),
		FExecuteAction::CreateRaw(this, &SCunstomTabWidget::OnFindBtnClicked)
	);
	MenuBuilder.AddMenuEntry(
		FText::FromString(TEXT("Delete")),
		FText::FromString(TEXT("Delete selected asset")),
		FSlateIcon(),
		FExecuteAction::CreateRaw(this, &SCunstomTabWidget::OnDeleteBtnClicked)
	);

	return MenuBuilder.MakeWidget();
}

void SCunstomTabWidget::OnFindBtnClicked()
{
	TArray<TSharedPtr<FAssetData>> SelectedItems = m_ListView->GetSelectedItems();
	if (SelectedItems.IsEmpty())
	{
		return;
	}

	TArray<FString> AssetPaths;
	for (TSharedPtr<FAssetData> SelectedItem : SelectedItems)
		AssetPaths.Add(SelectedItem->GetObjectPathString());

	UEditorAssetLibrary::SyncBrowserToObjects(AssetPaths);
}

void SCunstomTabWidget::OnDeleteBtnClicked()
{
	TArray<TSharedPtr<FAssetData>> SelectedItems = m_ListView->GetSelectedItems();
	if (SelectedItems.IsEmpty())
	{
		return;
	}

	TArray<FAssetData> ToBeDeletedAssets;
	for (auto& SelectedItem : SelectedItems)
	{
		ToBeDeletedAssets.Add(*SelectedItem);
	}
	ObjectTools::DeleteAssets(ToBeDeletedAssets);
}

void SCunstomTabWidget::FilterAssets()
{
	m_FilteredAssets.Empty();
	m_SelectedAssets.Empty();
	if (m_FilterType == nullptr)
	{
		m_FilteredAssets = m_AssetsInFolderPath;
	}
	else
	{
		for (const auto& AssetData : m_AssetsInFolderPath)
		{
			if (AssetData->GetClass()->GetClassPathName() == *m_FilterType)
			{
				m_FilteredAssets.Add(AssetData);
			}
		}
	}
	m_ListView->RebuildList();
}

void SCunstomTabWidget::GetAssetsInFolderPath()
{
	m_AssetsInFolderPath.Empty();

	TArray<FString> AssetsPaths = UEditorAssetLibrary::ListAssets(m_FolderPath);
	for (const auto& AssetPath : AssetsPaths)
	{
		FAssetData AssetData = UEditorAssetLibrary::FindAssetData(AssetPath);
		if (AssetData.IsValid())
		{
			// Notice the MakeShareable and MakeShared
			m_AssetsInFolderPath.Emplace(MakeShared<FAssetData>(AssetData));
		}
	}
}
