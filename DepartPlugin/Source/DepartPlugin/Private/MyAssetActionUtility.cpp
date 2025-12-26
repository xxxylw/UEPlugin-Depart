// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAssetActionUtility.h"

#include "MyDebugger.h"
#include "EditorUtilityLibrary.h"


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
	TArray<UObject*> selectedAssets = UEditorUtilityLibrary::GetSelectedAssets();
	for (auto assest : selectedAssets)
	{
		const FString* prefix = prefixMap.Find(assest->GetClass());
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
