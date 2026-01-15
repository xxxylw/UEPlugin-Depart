// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomEditorUtilityWidget.h"

#include "Subsystems/EditorActorSubsystem.h"
#include "Engine/StaticMeshActor.h"
#include "Kismet/KismetMathLibrary.h"
#include "AssetToolsModule.h"
#include "Factories//MaterialFactoryNew.h"
#include "EditorAssetLibrary.h"
#include "Materials/MaterialExpressionTextureSample.h"
#include "EditorUtilityLibrary.h"
#include "EditorAssetLibrary.h"

#include "MyDebugger.h"

namespace Utils {
	static int32 FindLasetNumberLength(FString& Str)
	{
		int32 Length = 0;

		for (int32 i = Str.Len() - 1; i >= 0; --i)
		{
			if (FChar::IsDigit(Str[i]))
			{
				Length++;
			}
			else
			{
				break;
			}
		}

		return Length;
	}
}

#pragma region Actor
void UCustomEditorUtilityWidget::SelectedAllActorsWithSameMesh()
{
	GetEditorActorSubsystem();

	TArray<AActor*> SelectedActors = EditorActorSubsystem->GetSelectedLevelActors();
	if (SelectedActors.Num() == 0)
	{
		POPUP_WARN(TEXT("You have selected least 1 actor!"));
		return;
	}

	AActor* SelectedActor = SelectedActors[0];
#if 0 // Through Name
	FString ActorName = SelectedActor->GetActorLabel();
	FString NameToSearch = ActorName.LeftChop(Utils::FindLasetNumberLength(ActorName));

	TArray<AActor*> AllActors = EditorActorSubsystem->GetAllLevelActors();

	int32 SameNum = 0;
	for (auto Actor : AllActors)
	{
		if (Actor->GetActorLabel().Contains(NameToSearch))
		{
			EditorActorSubsystem->SetActorSelectionState(Actor, true);
			SameNum++;
		}
	}
	NOTIFY_SUCCESS(TEXT("Success:Selected %d actors"), SameNum);
#else
	AStaticMeshActor* BaseStaticMeshActor = Cast<AStaticMeshActor>(SelectedActor);
	if (!BaseStaticMeshActor)
	{
		POPUP_WARN(TEXT("You must selected a staticmesh actor!"));
	}
	TObjectPtr<UStaticMesh> BaseStaticMesh = BaseStaticMeshActor->GetStaticMeshComponent()->GetStaticMesh();
	
	TArray<AActor*> AllActors = EditorActorSubsystem->GetAllLevelActors();

	int32 SameNum = 0;
	for (auto Actor : AllActors)
	{
		if (Actor->GetClass() != AStaticMeshActor::StaticClass())
			continue;

		AStaticMeshActor* StaticMeshActor = Cast<AStaticMeshActor>(Actor);
		TObjectPtr<UStaticMesh> StaticMesh = StaticMeshActor->GetStaticMeshComponent()->GetStaticMesh();
		if (StaticMesh == BaseStaticMesh)
		{
			EditorActorSubsystem->SetActorSelectionState(Actor, true);
			SameNum++;
		}
	}
	NOTIFY_SUCCESS(TEXT("Success:Selected %d actors"), SameNum);
#endif
}

void UCustomEditorUtilityWidget::DuplicateSelectedActors()
{
	GetEditorActorSubsystem();

	TArray<AActor*> SelectedActors = EditorActorSubsystem->GetSelectedLevelActors();

	FVector Direction = m_DuplicateDirection.GetSafeNormal();
	for (auto Actor : SelectedActors)
	{
		for (int i = 0; i < m_DuplicateCount; i++)
		{
			FVector Offset = Direction * m_DuplicateInterval * (i + 1);
			AActor* DupliatedActor = EditorActorSubsystem->DuplicateActor(Actor, Actor->GetWorld(), Offset);
			EditorActorSubsystem->SetActorSelectionState(DupliatedActor, true);
		}
	}
}

void UCustomEditorUtilityWidget::RandomTranslateSelectedActors()
{
	GetEditorActorSubsystem();

	TArray<AActor*> SelectedActors = EditorActorSubsystem->GetSelectedLevelActors();

	FVector Normal = m_TranslateNormal.GetSafeNormal();
	if (Normal.IsNearlyZero())
	{
		UE_LOG(LogTemp, Warning, TEXT("Normal is zero!"));
		return;
	}

	FVector Arbitrary = FVector::RightVector;
	if (FMath::Abs(FVector::DotProduct(Arbitrary, Normal)) > 0.99f)
	{
		Arbitrary = FVector::UpVector;
	}
	FVector T1 = FVector::CrossProduct(Normal, Arbitrary).GetSafeNormal();
	FVector T2 = FVector::CrossProduct(Normal, T1).GetSafeNormal();

	for (auto Actor : SelectedActors)
	{
		if (!m_ActorsSavedLocation.Contains(Actor))
			m_ActorsSavedLocation.Add(Actor, TArray<FVector>());
		m_ActorsSavedLocation[Actor].Add(Actor->GetActorLocation());

		float a = FMath::RandRange(m_TranslateRange.X, m_TranslateRange.Y);
		float b = FMath::RandRange(m_TranslateRange.X, m_TranslateRange.Y);

		FVector Offset = a * T1 + b * T2;
		Actor->AddActorWorldOffset(Offset);
	}
}

void UCustomEditorUtilityWidget::RandomRotateSelectedActors()
{
	GetEditorActorSubsystem();

	TArray<AActor*> SelectedActors = EditorActorSubsystem->GetSelectedLevelActors();

	for (auto Actor : SelectedActors)
	{
		if (!m_ActorsSavedRotation.Contains(Actor))
			m_ActorsSavedRotation.Add(Actor, TArray<FQuat>());
		m_ActorsSavedRotation[Actor].Add(Actor->GetActorQuat());

		float AngleDeg = FMath::RandRange(m_RotateRange.X, m_RotateRange.Y);

		FVector Axis = m_RotateAxis.GetSafeNormal();
		FQuat Quat = FQuat(Axis, FMath::DegreesToRadians(AngleDeg));
		Actor->AddActorWorldRotation(Quat);
	}
}

void UCustomEditorUtilityWidget::RandomScaleSelectedActors()
{
	GetEditorActorSubsystem();

	TArray<AActor*> SelectedActors = EditorActorSubsystem->GetSelectedLevelActors();

	for (auto Actor : SelectedActors)
	{
		if (!m_ActorsSavedScale.Contains(Actor))
			m_ActorsSavedScale.Add(Actor, TArray<FVector>());
		m_ActorsSavedScale[Actor].Add(Actor->GetActorScale());

		float ScaleFactor = FMath::RandRange(m_ScaleRange.X, m_ScaleRange.Y);

		FVector NewScale = Actor->GetActorScale3D() * ScaleFactor;

		Actor->SetActorScale3D(NewScale);
	}
}

void UCustomEditorUtilityWidget::ResetAllSelectedActors()
{
	GetEditorActorSubsystem();

	TArray<AActor*> SelectedActors = EditorActorSubsystem->GetSelectedLevelActors();

	for (auto Actor : SelectedActors)
	{
		Actor->Modify();

		if (auto Saved = m_ActorsSavedLocation.Find(Actor))
		{
			if(Saved->Num() > 0)
				Actor->SetActorLocation(Saved->Pop());
			if (Saved->Num() == 0)
				m_ActorsSavedLocation.Remove(Actor);
		}

		if (auto Saved = m_ActorsSavedRotation.Find(Actor))
		{
			if (Saved->Num() > 0)
				Actor->SetActorRotation(Saved->Pop());
			if (Saved->Num() == 0)
				m_ActorsSavedLocation.Remove(Actor);
		}

		if (auto Saved = m_ActorsSavedScale.Find(Actor))
		{
			if (Saved->Num() > 0)
				Actor->SetActorScale3D(Saved->Pop());
			if (Saved->Num() == 0)
				m_ActorsSavedLocation.Remove(Actor);
		}
	}

	NOTIFY_SUCCESS(TEXT("Success:Reset %d actors"), SelectedActors.Num());
}

void UCustomEditorUtilityWidget::AdsorbedToSurface()
{
	GetEditorActorSubsystem();

	TArray<AActor*> SelectedActors = EditorActorSubsystem->GetSelectedLevelActors();

	for (auto Actor : SelectedActors)
	{
		if (!m_ActorsSavedLocation.Contains(Actor))
			m_ActorsSavedLocation.Add(Actor, TArray<FVector>());
		m_ActorsSavedLocation[Actor].Add(Actor->GetActorLocation());
		if (!m_ActorsSavedRotation.Contains(Actor))
			m_ActorsSavedRotation.Add(Actor, TArray<FQuat>());
		m_ActorsSavedRotation[Actor].Add(Actor->GetActorQuat());

		UWorld* World = Actor->GetWorld();
		FHitResult HitResult;
		FVector Start = Actor->GetActorLocation() + FVector::UpVector * 1000;
		FVector End = Actor->GetActorLocation() + FVector::DownVector * 1000;
		FCollisionQueryParams CollisionQueryParams;
		CollisionQueryParams.AddIgnoredActor(Actor);

		if (World->LineTraceSingleByChannel(
			HitResult,
			Start,
			End,
			ECollisionChannel::ECC_Visibility,
			CollisionQueryParams
		))
		{
			FRotator AlignRot = UKismetMathLibrary::MakeRotFromZX(
				HitResult.Normal,
				Actor->GetActorForwardVector()
			);
			Actor->SetActorLocation(HitResult.Location);
			Actor->SetActorRotation(AlignRot);
		}
	}
}

void UCustomEditorUtilityWidget::GetEditorActorSubsystem()
{
	if (!EditorActorSubsystem)
	{
		EditorActorSubsystem = GEditor->GetEditorSubsystem<UEditorActorSubsystem>();
	}
}

#pragma endregion // Actor

#pragma region Material

void UCustomEditorUtilityWidget::CreateMaterial()
{
	FAssetToolsModule& AssetToolsModule = 
		FModuleManager::LoadModuleChecked<FAssetToolsModule>(TEXT("AssetTools"));

	FString PackagePath = TEXT("/Game/Materials");
	FString CleanFileName = m_FileName.TrimStartAndEnd();
	if (CleanFileName.IsEmpty())
	{
		CleanFileName = TEXT("NewMaterial");
	}
	if (!CleanFileName.StartsWith(TEXT("M_")))
	{
		CleanFileName = TEXT("M_") + CleanFileName;
	}
	if (!UEditorAssetLibrary::DoesDirectoryExist(PackagePath))
	{
		if (!UEditorAssetLibrary::MakeDirectory(PackagePath))
		{
			POPUP_ERROR(TEXT("Failed to create directory: %s"), *PackagePath);
			return;
		}
	}

	FString UniquePackageName;
	FString UniqueAssetName;
	AssetToolsModule.Get().CreateUniqueAssetName(
		PackagePath / CleanFileName,
		TEXT(""),
		UniquePackageName,
		UniqueAssetName
	);

	UMaterialFactoryNew* MaterialFactory = NewObject<UMaterialFactoryNew>();
	UObject* NewAsset = AssetToolsModule.Get().CreateAsset(
		UniqueAssetName,
		FPackageName::GetLongPackagePath(UniquePackageName),
		UMaterial::StaticClass(),
		MaterialFactory
	);

	UMaterial* NewMaterial = Cast<UMaterial>(NewAsset);
	if (NewMaterial)
	{
		NOTIFY_SUCCESS(TEXT("Successfully created Material: %s"), *NewAsset->GetPathName());
		UEditorAssetLibrary::SaveAsset(NewAsset->GetPathName());
	}
	else
	{
			NOTIFY_SUCCESS(TEXT("Failed created Material: %s"), *UniqueAssetName);
		return;
	}

	// add texture node for material
	TArray<FAssetData> SelectedAssetDatas = UEditorUtilityLibrary::GetSelectedAssetData();
	TArray<UTexture2D*> SelectedTextures = CastSelectedAssetsToUTexture2D(SelectedAssetDatas);
	int32 OffsetY = 0;
	for (const auto& Texture : SelectedTextures)
	{
		CreateTextureNode(NewMaterial, Texture, FIntPoint(-500, 260 * OffsetY++));
	}

	UEditorAssetLibrary::SyncBrowserToObjects({ NewMaterial->GetPathName() });
}


TArray<UTexture2D*> UCustomEditorUtilityWidget::CastSelectedAssetsToUTexture2D(const TArray<FAssetData>& SelectedAssetDatas)
{
	TArray<UTexture2D*> FilteredAsssets;
	for (const auto& SelectedAssetData : SelectedAssetDatas)
	{
		if (SelectedAssetData.GetClass() == UTexture2D::StaticClass())
		{
			FilteredAsssets.Add(Cast<UTexture2D>(SelectedAssetData.GetAsset()));
		}
	}

	return FilteredAsssets;
}

void UCustomEditorUtilityWidget::CreateTextureNode(UMaterial* Material, UTexture2D* Texture, FIntPoint NodePos)
{
	UMaterialExpressionTextureSample* TextureSampleNode =
		NewObject<UMaterialExpressionTextureSample>(Material);
	if (!TextureSampleNode)
		return;

	FString TextureName = Texture->GetName();

	FTextureNodeParams NP;
	NP.Material = Material;
	NP.Texture = Texture;
	NP.SamplerNode = TextureSampleNode;

	ETextureCategory TextureType = GetTextureCategoryByName(TextureName);
	switch (TextureType)
	{
	case ETextureCategory::BaseColor:
	{
		NP.CompressionSettings = TextureCompressionSettings::TC_Default;
		NP.bSRGB = true;
		NP.SamplerType = EMaterialSamplerType::SAMPLERTYPE_Color;
		NP.InputMaterialProperty = EMaterialProperty::MP_BaseColor;
		NP.OutputIndex = 0;
		NP.NodePos = NodePos;
		break;
	}
	case ETextureCategory::Normal:
	{
		NP.CompressionSettings = TextureCompressionSettings::TC_Normalmap;
		NP.bSRGB = false;
		NP.SamplerType = EMaterialSamplerType::SAMPLERTYPE_Normal;
		NP.InputMaterialProperty = EMaterialProperty::MP_Normal;
		NP.OutputIndex = 0;
		NP.NodePos = NodePos;
		break;
	}
	case ETextureCategory::Roughness:
	{
		NP.CompressionSettings = TextureCompressionSettings::TC_Default;
		NP.bSRGB = false;
		NP.SamplerType = EMaterialSamplerType::SAMPLERTYPE_LinearColor;
		NP.InputMaterialProperty = EMaterialProperty::MP_Roughness;
		NP.OutputIndex = 0;
		NP.NodePos = NodePos;
		break;
	}
	case ETextureCategory::Metallic:
	{
		NP.CompressionSettings = TextureCompressionSettings::TC_Default;
		NP.bSRGB = false;
		NP.SamplerType = EMaterialSamplerType::SAMPLERTYPE_LinearColor;
		NP.InputMaterialProperty = EMaterialProperty::MP_Metallic;
		NP.OutputIndex = 0;
		NP.NodePos = NodePos;
		break;
	}
	case ETextureCategory::Specular:
	{
		NP.CompressionSettings = TextureCompressionSettings::TC_Default;
		NP.bSRGB = false;
		NP.SamplerType = EMaterialSamplerType::SAMPLERTYPE_LinearColor;
		NP.InputMaterialProperty = EMaterialProperty::MP_Specular;
		NP.OutputIndex = 0;
		NP.NodePos = NodePos;
		break;
	}
	case ETextureCategory::Opacity:
	{
		NP.CompressionSettings = TextureCompressionSettings::TC_Default;
		NP.bSRGB = false;
		NP.SamplerType = EMaterialSamplerType::SAMPLERTYPE_LinearColor;
		NP.InputMaterialProperty = EMaterialProperty::MP_Opacity;
		NP.OutputIndex = 0;
		NP.NodePos = NodePos;
		break;
	}
	case ETextureCategory::AmbientOcclusion:
	{
		NP.CompressionSettings = TextureCompressionSettings::TC_Default;
		NP.bSRGB = false;
		NP.SamplerType = EMaterialSamplerType::SAMPLERTYPE_LinearColor;
		NP.InputMaterialProperty = EMaterialProperty::MP_AmbientOcclusion;
		NP.OutputIndex = 0;
		NP.NodePos = NodePos;
		break;
	}
	case ETextureCategory::Unknown:
	{
		POPUP_ERROR(TEXT("Unknown ETextureCategory for: %s"), *Texture->GetName());
		TextureSampleNode->MarkAsGarbage();
		return;
	}
	}

	ApplySamplerToMaterialProperty(NP);
}

void UCustomEditorUtilityWidget::ApplySamplerToMaterialProperty(FTextureNodeParams& NP)
{
	if (NP.Material->GetExpressionInputForProperty(NP.InputMaterialProperty)->IsConnected())
	{
		NOTIFY_WARN(TEXT("The InputMaterialProperty has Connected"));
		if (NP.SamplerNode) NP.SamplerNode->MarkAsGarbage();
		return;
	}
	// setup Texture
	NP.Texture->CompressionSettings = NP.CompressionSettings;
	NP.Texture->SRGB = NP.bSRGB;
	NP.Texture->PostEditChange();

	// set up node
	NP.SamplerNode->Texture = NP.Texture;
	NP.SamplerNode->SamplerType = NP.SamplerType;

	NP.SamplerNode->MaterialExpressionEditorX += NP.NodePos.X;
	NP.SamplerNode->MaterialExpressionEditorY += NP.NodePos.Y;

	// set up material
	NP.Material->GetExpressionCollection().AddExpression(NP.SamplerNode);
	NP.Material->GetExpressionInputForProperty(NP.InputMaterialProperty)->Connect(NP.OutputIndex, NP.SamplerNode);
	NP.Material->PostEditChange();
}

ETextureCategory UCustomEditorUtilityWidget::GetTextureCategoryByName(const FString& InTextureName)
{
	for (const auto& Pair : m_PostfixMap)
	{
		if (InTextureName.EndsWith(Pair.Key, ESearchCase::IgnoreCase))
		{
			return Pair.Value;
		}
	}
	return ETextureCategory::Unknown;
}

#pragma endregion
