// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetActionUtility.h"

#include "Materials/MaterialInstanceConstant.h"
#include "NiagaraSystem.h"

#include "MyAssetActionUtility.generated.h"

/**
 * 
 */
UCLASS()
class DEPARTPLUGIN_API UMyAssetActionUtility : public UAssetActionUtility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(CallInEditor)
	void Text();

	UFUNCTION(CallInEditor)
	void AddPrefix();

	UFUNCTION(CallInEditor)
	void Duplicate(int Count);

private:
	TMap<UClass*, FString> m_PrefixMap =
	{
		{	UBlueprint::StaticClass(),					TEXT("BP_")},
		{	UMaterial::StaticClass(),					TEXT("M_")},
		{	UMaterialInstanceConstant::StaticClass(),	TEXT("MI_")},
		{	UNiagaraSystem::StaticClass(),				TEXT("NS_")},
		{	UStaticMesh::StaticClass(),					TEXT("SM_")},
		{	UTexture2D::StaticClass(),					TEXT("T_")},
	};
};
