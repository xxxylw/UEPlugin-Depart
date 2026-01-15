// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "CustomEditorUtilityWidget.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class ETextureCategory : uint8
{
	Unknown,
	BaseColor,
	Normal,
	Roughness,
	Metallic,
	Specular,
	Opacity,
	AmbientOcclusion
};

UCLASS()
class DEPARTPLUGIN_API UCustomEditorUtilityWidget : public UEditorUtilityWidget
{
	GENERATED_BODY()
	
#pragma region Actor
private:
	UFUNCTION(BlueprintCallable, Category = "Depart.SelectedAll")
	void SelectedAllActorsWithSameMesh();

	UFUNCTION(BlueprintCallable, Category = "Depart.Duplicate")
	void DuplicateSelectedActors();

	UFUNCTION(BlueprintCallable, Category = "Depart.Translate")
	void RandomTranslateSelectedActors();

	UFUNCTION(BlueprintCallable, Category = "Depart.Rotate")
	void RandomRotateSelectedActors();

	UFUNCTION(BlueprintCallable, Category = "Depart.Scale")
	void RandomScaleSelectedActors();

	UFUNCTION(BlueprintCallable, Category = "Depart.Reset")
	void ResetAllSelectedActors();

	UFUNCTION(BlueprintCallable, Category = "Depart.Adsorb")
	void AdsorbedToSurface();

private:
	void GetEditorActorSubsystem();

protected:
	UPROPERTY(EditAnywhere, Category = "Depart.Duplicate")
	FVector m_DuplicateDirection;

	UPROPERTY(EditAnywhere, Category = "Depart.Duplicate")
	float m_DuplicateInterval;

	UPROPERTY(EditAnywhere, Category = "Depart.Duplicate")
	int32 m_DuplicateCount;

	UPROPERTY(EditAnywhere, Category = "Depart.Translate")
	FVector m_TranslateNormal;

	UPROPERTY(EditAnywhere, Category = "Depart.Translate")
	FVector2D m_TranslateRange;

	UPROPERTY(EditAnywhere, Category = "Depart.Rotate")
	FVector m_RotateAxis;

	UPROPERTY(EditAnywhere, Category = "Depart.Rotate")
	FVector2D m_RotateRange;

	UPROPERTY(EditAnywhere, Category = "Depart.Scale")
	FVector2D m_ScaleRange;

private:
	class UEditorActorSubsystem*			EditorActorSubsystem;
	TMap<AActor*, TArray<FVector>>			m_ActorsSavedLocation;
	TMap<AActor*, TArray<FQuat>>			m_ActorsSavedRotation;
	TMap<AActor*, TArray<FVector>>			m_ActorsSavedScale;

#pragma endregion // Actor

#pragma region Material

private:
	struct FTextureNodeParams
	{
		UMaterial* Material = nullptr;
		UTexture2D* Texture = nullptr;
		class UMaterialExpressionTextureSample* SamplerNode = nullptr;
		TextureCompressionSettings        CompressionSettings = TC_Default;
		bool                              bSRGB = true;
		EMaterialSamplerType              SamplerType = SAMPLERTYPE_Color;
		EMaterialProperty                 InputMaterialProperty = MP_BaseColor;
		int32							  OutputIndex;
		FIntPoint						  NodePos = FIntPoint(-500, 0);
	};

	UFUNCTION(BlueprintCallable)
	void CreateMaterial();
	TArray<UTexture2D*> CastSelectedAssetsToUTexture2D(const TArray<FAssetData>& SelectedAssetDatas);
	 
	void CreateTextureNode(UMaterial* Material, UTexture2D* Texture, FIntPoint NodePos);

	void ApplySamplerToMaterialProperty(FTextureNodeParams& TextureNodeParams);

	ETextureCategory GetTextureCategoryByName(const FString& InTextureName);
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Depart.Material")
	FString m_FileName;

	UPROPERTY(EditAnywhere, Category = "Depart.Material")
	TMap<FString, ETextureCategory> m_PostfixMap =
	{
		{TEXT("_D"),							ETextureCategory::BaseColor},
		{TEXT("_M"),							ETextureCategory::Metallic},
		{TEXT("_S"),							ETextureCategory::Specular},
		{TEXT("_R"),							ETextureCategory::Roughness},
		{TEXT("_N"),							ETextureCategory::Normal},
		{TEXT("_AO"),							ETextureCategory::AmbientOcclusion},
		{TEXT("_O"),							ETextureCategory::Opacity},

		{TEXT("_Diffuse"),						ETextureCategory::BaseColor},
		{TEXT("_BaseColor"),					ETextureCategory::BaseColor},

		{TEXT("_metal"),						ETextureCategory::Metallic},
		{TEXT("_metallic"),						ETextureCategory::Metallic},

		{TEXT("_nor"),							ETextureCategory::Normal},
		{TEXT("_normal"),						ETextureCategory::Normal},


		{TEXT("_ambientocclusion"),				ETextureCategory::AmbientOcclusion},

		{TEXT("_Roughness"),					ETextureCategory::Roughness},
	};

#pragma endregion // Material
};
