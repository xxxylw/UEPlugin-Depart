// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomTabWidget.h"
#include "CustomTableRow.h"
#include "MyDebugger.h"

#include "EditorAssetLibrary.h"





void SCunstomTabWidget::Construct(const FArguments& InArgs)
{	
	m_ComboboxFilterMap.GetKeys(m_ComboboxSrcOpts);

	TArray<FString> AssetsPaths = UEditorAssetLibrary::ListAssets(InArgs._FolderPath);
	for (const auto& AssetPath : AssetsPaths)
	{
		FAssetData AssetData = UEditorAssetLibrary::FindAssetData(AssetPath);
		if (AssetData.IsValid())
		{
			m_AssetsInFolderPath.Emplace(MakeShared<FAssetData>(AssetData));
		}

		// Notice the MakeShareable and MakeShared
		m_FilteredAssets = m_AssetsInFolderPath;
	}

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
					.Text(FText::FromString(TEXT("Option")))
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
		SAssignNew(m_CustomListView, SListView<TSharedPtr<FAssetData>>)
		.ListItemsSource(&m_AssetsInFolderPath)
		.OnGenerateRow_Lambda([this](TSharedPtr<FAssetData> Item, const TSharedRef<STableViewBase>& OwnerTable)
			{
				return
					SNew(SCustomTableRow, OwnerTable)
					.AssetData(Item)
					.OwnerWidget(SharedThis(this))
					;
			})
		.HeaderRow(SetupHeaderRow())
		;

	return m_CustomListView.ToSharedRef();
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
	
	const FTopLevelAssetPath* FilterClass = m_ComboboxFilterMap.Find(InSelection);
	m_FilteredAssets.Empty();
	m_SelectedAssets.Empty();

	if (!FilterClass)
	{
		return;
	}
	if (!FilterClass->IsValid())
	{
		m_FilteredAssets = m_AssetsInFolderPath;
	}
	else
	{
		for (const auto& AssetData : m_AssetsInFolderPath)
		{
			if (AssetData->GetClass()->GetClassPathName() == *FilterClass)
			{
				m_FilteredAssets.Add(AssetData);
			}
		}
	}

	m_CustomListView->SetListItemsSource(m_FilteredAssets);
	m_CustomListView->RebuildList();
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
