// Fill out your copyright notice in the Description page of Project Settings.

#include "EditorAssetLibrary.h"

#include "CustomTableRow.h"
#include "MyDebugger.h"



void SCustomTableRow::Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTable)
{
	m_AssetData = InArgs._AssetData;

	FSuperRowType::Construct(FSuperRowType::FArguments(), OwnerTable);

	SetPadding(FMargin(0, 3));

}

TSharedRef<SWidget> SCustomTableRow::GenerateWidgetForColumn(const FName& InColumnName)
{
	//if (!m_AssetData->IsValid())
	//{
	//	return SNullWidget::NullWidget;
	//}
	FTextBlockStyle TextBlockStyle = FTextBlockStyle::GetDefault();
	TextBlockStyle.ColorAndOpacity = FSlateColor(FColor::Silver);
	TextBlockStyle.SetShadowColorAndOpacity(FColor::Silver);
	TextBlockStyle.Font.TypefaceFontName = FName("Bold");


	if (InColumnName.IsEqual(CustomTabColumns::Asset))
	{
		return 
			SNew(STextBlock)
			.Text(FText::FromString(m_AssetData->AssetName.ToString()))
			.TextStyle(&TextBlockStyle)
			;
	}
	else if(InColumnName.IsEqual(CustomTabColumns::Class))
	{
		return
			SNew(STextBlock)
			.Text(FText::FromString(m_AssetData->GetClass()->GetName()));
	}
	else if (InColumnName.IsEqual(CustomTabColumns::Referencers))
	{
		int32 ReferencersNum = UEditorAssetLibrary::FindPackageReferencersForAsset(
			m_AssetData->GetObjectPathString()).Num();
		return
			SNew(STextBlock)
			.Text(FText::FromString(FString::FromInt(ReferencersNum)));
	}
	else if (InColumnName.IsEqual(CustomTabColumns::Selected))
	{
		return
			SNew(SCheckBox)
			.OnCheckStateChanged(this, &SCustomTableRow::OnTableRowCheckBoxStateChanged)
			;
	}
	return SNullWidget::NullWidget;
}

void SCustomTableRow::OnTableRowCheckBoxStateChanged(ECheckBoxState CheckBoxState)
{
	switch (CheckBoxState)
	{
	case ECheckBoxState::Unchecked:
		SCREEN_LOG(FString::Printf(TEXT("%s Unchecked"), *m_AssetData->GetAsset()->GetName()));
		break;
	case ECheckBoxState::Checked:
		SCREEN_LOG(FString::Printf(TEXT("%s Checked"), *m_AssetData->GetAsset()->GetName()));
		break;
	default:
		break;
	}
}
