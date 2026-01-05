// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomStyle.h"

#include "Styling/SlateStyleRegistry.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

// for svg
#define RootToContentDir StyleSet->RootToContentDir

void FCustomStyle::Initialize()
{
	if (!s_StyleInstance)
	{
		s_StyleInstance = CreateInstance();
		FSlateStyleRegistry::RegisterSlateStyle(*s_StyleInstance);
	}
}

void FCustomStyle::Shutdown()
{
	if (s_StyleInstance)
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*s_StyleInstance);
		s_StyleInstance.Reset();
	}
}

const ISlateStyle& FCustomStyle::Get()
{
	return *s_StyleInstance;
}

FName FCustomStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("CustomStyle"));
	return StyleSetName;
}

void FCustomStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

TSharedRef<FSlateStyleSet> FCustomStyle::CreateInstance()
{
	TSharedRef<FSlateStyleSet> StyleSet = 
		MakeShared<FSlateStyleSet>(GetStyleSetName());;
	
	const FVector2D Icon16x16(16.0f, 16.0f);
	const FVector2D Icon32x32(32.0f, 32.0f);
	const FVector2D Icon64x64(64.0f, 64.0f);

	const FString IconPath = IPluginManager::Get()
		.FindPlugin(FString("DepartPlugin"))->GetBaseDir() / TEXT("Resources");
	StyleSet->SetContentRoot(IconPath);

	// png
	StyleSet->Set(CustomStyleSetName::Bear,				new FSlateImageBrush(IconPath / CustomStyleSetPath::Bear,			Icon32x32));
	StyleSet->Set(CustomStyleSetName::Candy,			new FSlateImageBrush(IconPath / CustomStyleSetPath::Candy,			Icon32x32));
	StyleSet->Set(CustomStyleSetName::Christmas,		new FSlateImageBrush(IconPath / CustomStyleSetPath::Christmas,		Icon32x32));
	StyleSet->Set(CustomStyleSetName::ChristmasSock,	new FSlateImageBrush(IconPath / CustomStyleSetPath::ChristmasSock,	Icon32x32));
	StyleSet->Set(CustomStyleSetName::ChristmasTree,	new FSlateImageBrush(IconPath / CustomStyleSetPath::ChristmasTree,	Icon32x32));
	StyleSet->Set(CustomStyleSetName::Gift,				new FSlateImageBrush(IconPath / CustomStyleSetPath::Gift,			Icon32x32));
	StyleSet->Set(CustomStyleSetName::ReinDeer,			new FSlateImageBrush(IconPath / CustomStyleSetPath::ReinDeer,		Icon32x32));
	StyleSet->Set(CustomStyleSetName::SantaClaus,		new FSlateImageBrush(IconPath / CustomStyleSetPath::SantaClaus,		Icon32x32));
	StyleSet->Set(CustomStyleSetName::SnowGlobe,		new FSlateImageBrush(IconPath / CustomStyleSetPath::SnowGlobe,		Icon32x32));
	StyleSet->Set(CustomStyleSetName::SnowMan,			new FSlateImageBrush(IconPath / CustomStyleSetPath::SnowMan,		Icon32x32));
	StyleSet->Set(CustomStyleSetName::Star,				new FSlateImageBrush(IconPath / CustomStyleSetPath::Star,			Icon32x32));
	
	// svg
	StyleSet->Set(CustomStyleSetName::ChristmasHat,		new IMAGE_BRUSH_SVG(CustomStyleSetPath::ChristmasHat, Icon32x32));
	return StyleSet;
}

TSharedPtr<FSlateStyleSet> FCustomStyle::s_StyleInstance = nullptr;
