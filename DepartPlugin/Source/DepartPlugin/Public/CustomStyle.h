// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Styling/SlateStyle.h"

/**
 * 
 */

namespace CustomStyleSetName
{
	// png
	inline const FName Bear(TEXT("Bear"));
	inline const FName Candy(TEXT("Candy"));
	inline const FName Christmas(TEXT("Christmas"));
	inline const FName ChristmasSock(TEXT("ChristmasSock"));
	inline const FName ChristmasTree(TEXT("ChristmasTree"));
	inline const FName Gift(TEXT("Gift"));
	inline const FName ReinDeer(TEXT("ReinDeer"));
	inline const FName SantaClaus(TEXT("SantaClaus"));
	inline const FName SnowGlobe(TEXT("SnowGlobe"));
	inline const FName SnowMan(TEXT("SnowMan"));
	inline const FName Star(TEXT("Star"));

	// svg
	inline const FName ChristmasHat(TEXT("ChristmasHat"));
}

namespace CustomStyleSetPath
{
	// png
	inline const FString Bear(TEXT("bear.png"));
	inline const FString Candy(TEXT("candy.png"));
	inline const FString Christmas(TEXT("christmas.png"));
	inline const FString ChristmasSock(TEXT("christmas-sock.png"));
	inline const FString ChristmasTree(TEXT("christmas-tree.png"));
	inline const FString Gift(TEXT("gift.png"));
	inline const FString ReinDeer(TEXT("reindeer.png"));
	inline const FString SantaClaus(TEXT("santa-claus.png"));
	inline const FString SnowGlobe(TEXT("snow-globe.png"));
	inline const FString SnowMan(TEXT("snowman.png"));
	inline const FString Star(TEXT("star.png"));

	// svg
	inline const FString ChristmasHat(TEXT("christmas-hat"));
}

class FCustomStyle {
public:
	static void Initialize();
	static void Shutdown();

	static const ISlateStyle& Get();

	static FName GetStyleSetName();

	static void ReloadTextures();

private:
	static TSharedRef<FSlateStyleSet> CreateInstance();

private:
	static TSharedPtr<FSlateStyleSet> s_StyleInstance;
};