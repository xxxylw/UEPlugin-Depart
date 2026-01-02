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
	

private: // Small Fuc
	TSharedRef<SWidget> CreateComboBox();
	TSharedRef<SWidget> CreateListView();
	TSharedRef<SWidget> CreateButtonList();

	TSharedPtr<SHeaderRow> SetupHeaderRow();

	FReply OnInverseButtonClicked();
	FReply OnPrintButtonClicked();
	void OnHeaderRowCheckBoxStateChanged(ECheckBoxState CheckBoxState);
	void OnComboBoxSelectionChanged(TSharedPtr<FString> InSelection, ESelectInfo::Type InSelectInfo);

private:
	TArray<TSharedPtr<FString>>		m_ComboboxSrcOpts;
	TArray<TSharedPtr<FAssetData>>	m_ListViewSrcOpts;
};