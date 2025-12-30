// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomTableRow.h"

void SCustomTableRow::Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTable)
{
	m_AssetData = InArgs._AssetData;

	FSuperRowType::Construct(FSuperRowType::FArguments(), OwnerTable);

}

TSharedRef<SWidget> SCustomTableRow::GenerateWidgetForColumn(const FName& InColumnName)
{
	//if (!m_AssetData->IsValid())
	//{
	//	return SNullWidget::NullWidget;
	//}

	if (InColumnName.IsEqual(CustomTabColumns::Asset))
	{
		return 
			SNew(STextBlock)
			.Text(FText::FromString(m_AssetData->AssetName.ToString()));
	}
	else if(InColumnName.IsEqual(CustomTabColumns::Class))
	{
		return
			SNew(STextBlock)
			.Text(FText::FromString(m_AssetData->GetClass()->GetName()));
	}
	else if (InColumnName.IsEqual(CustomTabColumns::Referencers))
	{
	}
	return SNullWidget::NullWidget;
}
