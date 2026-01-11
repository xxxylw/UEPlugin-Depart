// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomEditorUtilityWidget.h"

#include "Subsystems/EditorActorSubsystem.h"
#include "Engine/StaticMeshActor.h"

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
		}

		if (auto Saved = m_ActorsSavedRotation.Find(Actor))
		{
			Actor->SetActorRotation(Saved->Pop());
		}

		if (auto Saved = m_ActorsSavedScale.Find(Actor))
		{
			Actor->SetActorScale3D(Saved->Pop());
		}
	}

	NOTIFY_SUCCESS(TEXT("Success:Reset %d actors"), SelectedActors.Num());
}

void UCustomEditorUtilityWidget::GetEditorActorSubsystem()
{
	if (!EditorActorSubsystem)
	{
		EditorActorSubsystem = GEditor->GetEditorSubsystem<UEditorActorSubsystem>();
	}
}
