// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "CustomEditorUtilityWidget.generated.h"

/**
 * 
 */
UCLASS()
class DEPARTPLUGIN_API UCustomEditorUtilityWidget : public UEditorUtilityWidget
{
	GENERATED_BODY()
	
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
};
