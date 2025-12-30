// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Widgets/Views/StableRow.h"
/**
 * 
 */

namespace CustomTabColumns
{
	inline const FName Asset(TEXT("Asset"));
	inline const FName Class(TEXT("Class"));
	inline const FName Referencers(TEXT("Referencers"));
}

class SCustomTableRow : public SMultiColumnTableRow<TSharedPtr<FAssetData>>
{
	SLATE_BEGIN_ARGS(SCustomTableRow) {}
		SLATE_ARGUMENT(TSharedPtr<FAssetData>, AssetData)
	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTable);

	virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& InColumnName) override;
private:
	TSharedPtr<FAssetData> m_AssetData;
};

