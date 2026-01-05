// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAssetActionUtility.h"

#include "MyDebugger.h"
#include "EditorUtilityLibrary.h"
#include "EditorAssetLibrary.h"
#include "AssetRegistry/AssetRegistryModule.h"

namespace Utils{
	static FString IncrementNameSuffix(const FString& InName)
	{
		FString BaseName = InName;
		int32 Number = 0;

		// 从后往前找连续数字
		int32 Index = BaseName.Len() - 1;
		while (Index >= 0 && FChar::IsDigit(BaseName[Index]))
		{
			Index--;
		}

		// 如果有数字后缀
		if (Index < BaseName.Len() - 1)
		{
			FString NumberStr = BaseName.Mid(Index + 1);
			Number = FCString::Atoi(*NumberStr);
			BaseName = BaseName.Left(Index + 1);
		}
		else
		{
			// 没有数字，默认从 1 开始
			Number = 0;
		}

		Number++;
		return FString::Printf(TEXT("%s%d"), *BaseName, Number);
	}
};
void UMyAssetActionUtility::Text()
{
#pragma region Log Example
	/*
	SCREEN_LOG(TEXT("Hello age : %d"), 12);

	// Log in Log Output
	LOG_LOG(TEXT("I'm in UE %s"), TEXT("Log"));
	LOG_WARNING(TEXT("I'm in UE Warning"));
	LOG_ERROR(TEXT("I'm in UE Error"));

	// Log in Popup Window
	POPUP_WARN(TEXT("You re in Popup Warn!"));

	// Dialog
	NOTIFY_SUCCESS(TEXT("Notify Success"));
	*/
#pragma endregion Log Example
}

void UMyAssetActionUtility::AddPrefix()
{
	FAssetRegistryModule& AssetRegistryModule =
		FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");

	TArray<UObject*> selectedAssets = UEditorUtilityLibrary::GetSelectedAssets();
	for (auto assest : selectedAssets)
	{
		const FString* prefix = m_PrefixMap.Find(assest->GetClass());
		if (prefix != nullptr)
		{
			FString newName, oldName = assest->GetName();
			if (oldName.StartsWith(*prefix))
				continue;
			if (assest->IsA<UMaterialInstanceConstant>())
			{
				oldName.RemoveFromEnd("_Inst");
				oldName.RemoveFromStart("M_");
			}
			newName = *prefix + oldName;

			FString packagePath = assest->GetOutermost()->GetName();
			FString longPackagePath = FPackageName::GetLongPackagePath(packagePath);

			auto MakeObjectPath = [&](const FString& Name)
				{
					return longPackagePath + TEXT("/") + Name + TEXT(".") + Name;
				};

			FAssetData existingAsset =
				AssetRegistryModule.Get().GetAssetByObjectPath(*MakeObjectPath(newName));

			while (existingAsset.IsValid())
			{
				newName = Utils::IncrementNameSuffix(newName);
				existingAsset =
					AssetRegistryModule.Get().GetAssetByObjectPath(*MakeObjectPath(newName));
			}
			assest->Modify();
			UEditorUtilityLibrary::RenameAsset(assest, newName);
		}
		else
		{
			// *FString -> TChar*
			SCREEN_WARN(FString::Printf(TEXT("Can't find class %s"), *assest->GetClass()->GetName()));
			LOG_WARNING(TEXT("Can't find class %s in PrefixMap"), *assest->GetClass()->GetName());
		}
	}
}

void UMyAssetActionUtility::Duplicate(int Count)
{
	if (Count <= 0 || Count > 10)
	{
		SCREEN_WARN(TEXT("Please Enter a Valid number!(1 - 10)"));
		return;
	}

	FAssetRegistryModule& AssetRegistryModule =
		FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");

	TArray<FAssetData> AssetDatas = UEditorUtilityLibrary::GetSelectedAssetData();
	for (const auto& AssetData : AssetDatas)
	{
		UObject* Asset = AssetData.GetAsset();
		if (!Asset)
		{
			continue;
		}

		const FString* Prefix = m_PrefixMap.Find(Asset->GetClass());
		FString BaseName = Asset->GetName();

		if (!Prefix)
		{
			SCREEN_WARN(FString::Printf(
				TEXT("Can't find class %s"), *Asset->GetClass()->GetName()));
			continue;
		}

		if (Asset->IsA<UMaterialInstanceConstant>())
		{
			BaseName.RemoveFromEnd(TEXT("_Inst"));
			BaseName.RemoveFromStart(TEXT("M_"));
		}

		FString PackagePath = Asset->GetOutermost()->GetName();
		FString LongPackagePath = FPackageName::GetLongPackagePath(PackagePath);

		auto MakeObjectPath = [&](const FString& Name)
			{
				return LongPackagePath + TEXT("/") + Name + TEXT(".") + Name;
			};

		for (int32 i = 0; i < Count; ++i)
		{
			FString NewName = BaseName.StartsWith(*Prefix) ? BaseName : *Prefix + BaseName;

			FAssetData ExistingAsset =
				AssetRegistryModule.Get().GetAssetByObjectPath(*MakeObjectPath(NewName));

			while (ExistingAsset.IsValid())
			{
				NewName = Utils::IncrementNameSuffix(NewName);
				ExistingAsset =
					AssetRegistryModule.Get().GetAssetByObjectPath(*MakeObjectPath(NewName));
			}

			// Duplicate
			const FString SourcePath = AssetData.GetObjectPathString();
			const FString DestPath = MakeObjectPath(NewName);

			UEditorAssetLibrary::DuplicateAsset(SourcePath, DestPath);
			UEditorAssetLibrary::SaveAsset(DestPath);
		}
	}
}
