// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Widgets/SCompoundWidget.h"

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
	TSharedRef<SWidget> CreateComboBox();
	TSharedRef<SWidget> CreateListView();
	TSharedRef<SWidget> CreateButtonList();

private: // Small Fuc
	TSharedPtr<SHeaderRow> SetupHeaderRow();

private:
	TArray<TSharedPtr<FString>>		m_ComboboxSrcOpts;
	TArray<TSharedPtr<FAssetData>>	m_ListViewSrcOpts;
};