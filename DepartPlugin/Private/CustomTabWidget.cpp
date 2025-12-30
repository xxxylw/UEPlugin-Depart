// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomTabWidget.h"
#include "CustomTableRow.h"

#include "EditorAssetLibrary.h"





void SCunstomTabWidget::Construct(const FArguments& InArgs)
{	
	m_ComboboxSrcOpts.Add(MakeShareable(new FString(TEXT("Option1"))));
	m_ComboboxSrcOpts.Add(MakeShareable(new FString(TEXT("Option2"))));
	m_ComboboxSrcOpts.Add(MakeShareable(new FString(TEXT("Option3"))));

	TArray<FString> AssetsPaths = UEditorAssetLibrary::ListAssets(InArgs._FolderPath);
	for (const auto& AssetPath : AssetsPaths)
	{
		FAssetData AssetData = UEditorAssetLibrary::FindAssetData(AssetPath);
		if (AssetData.IsValid())
		{
			m_ListViewSrcOpts.Emplace(MakeShared<FAssetData>(AssetData));
		}
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
		.AutoWidth()
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
				[
					SNew(STextBlock)
					.Text(FText::FromString(TEXT("Option")))
				]
		]
		;
	return CustomComboBox;
}

TSharedRef<SWidget> SCunstomTabWidget::CreateListView()
{
	TSharedRef<SWidget> CustomListView =
		SNew(SListView<TSharedPtr<FAssetData>>)
		.ListItemsSource(&m_ListViewSrcOpts)
		.OnGenerateRow_Lambda([](TSharedPtr<FAssetData> Item, const TSharedRef<STableViewBase>& OwnerTable)
			{
				return
					SNew(SCustomTableRow, OwnerTable)
					.AssetData(Item)
					;
			})
		.HeaderRow(SetupHeaderRow())
		;

	return CustomListView;
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
			.Text(FText::FromString(TEXT("Button1")))
		]
		+ SHorizontalBox::Slot()
		.VAlign(VAlign_Center)
		.Padding(5.5)
		.AutoWidth()
		[
			SNew(SButton)
			.Text(FText::FromString(TEXT("Button2")))
		]
	;
	return ButtonList;
}

TSharedPtr<SHeaderRow> SCunstomTabWidget::SetupHeaderRow()
{
	TSharedPtr<SHeaderRow> CustomHeaderRow = 
		SNew(SHeaderRow)
		+ SHeaderRow::Column(CustomTabColumns::Asset)
		.DefaultLabel(FText::FromString(CustomTabColumns::Asset.ToString()))

		+ SHeaderRow::Column(CustomTabColumns::Class)
		.DefaultLabel(FText::FromString(CustomTabColumns::Class.ToString()))

		+ SHeaderRow::Column(CustomTabColumns::Referencers)
		.DefaultLabel(FText::FromString(CustomTabColumns::Referencers.ToString()))
		;

	return CustomHeaderRow;
}
