#pragma once

#include "CoreMinimal.h"
#include "Logging/LogMacros.h"

#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"

DECLARE_LOG_CATEGORY_EXTERN(DP_LOG, Log, All)
DEFINE_LOG_CATEGORY(DP_LOG)

// Log on Screen
inline void ScreenDebugMessageImpl(const FColor& Color, const float& Duration, const FString& Message)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, Duration, Color, Message);
	}
}

inline void PopupMessageImpl(EAppMsgType::Type MsgType, const FString& Message, const FString& Title)
{
	if (!IsRunningCommandlet())
	{
		FMessageDialog::Open(MsgType, FText::FromString(Message), FText::FromString(Title));
	}
}

inline void NotificationMessageImpl(const FColor& Color, float Duration, const FString& Message)
{
	FNotificationInfo Info(FText::FromString(Message));
	Info.bUseThrobber = false;
	Info.bUseSuccessFailIcons = true;
	Info.ExpireDuration = Duration;
	Info.FadeInDuration = 0.1f;
	Info.FadeOutDuration = 0.5f;

	if (Color == FColor::Red || Color == FColor::Orange)
	{
		Info.Image = FCoreStyle::Get().GetBrush(TEXT("MessageLog.WarningIcon"));
	}
	else if (Color == FColor::Green)
	{
		Info.Image = FCoreStyle::Get().GetBrush(TEXT("MessageLog.SuccessIcon"));
	}

	FSlateNotificationManager::Get().AddNotification(Info);
}



// Macro
//#define SCREEN_DEBUG(Color, Duration, Format, ...)	ScreenDebugMessageImpl(Color, Duration, FString::Printf(Format, ##__VA_ARGS__))
//#define SCREEN_LOG(...)								SCREEN_DEBUG(FColor::Yellow, 5.0f, __VA_ARGS__)
//#define SCREEN_WARN(...)							SCREEN_DEBUG(FColor::Orange, 5.0f, __VA_ARGS__)
//#define SCREEN_ERROR(...)							SCREEN_DEBUG(FColor::Red, 8.0f, __VA_ARGS__)
//#define SCREEN_SUCCESS(...)							SCREEN_DEBUG(FColor::Green, 5.0f, __VA_ARGS__)

#define SCREEN_LOG(Msg)								ScreenDebugMessageImpl(FColor::White, 5.0f, Msg)
#define SCREEN_WARN(Msg)							ScreenDebugMessageImpl(FColor::Yellow, 5.0f, Msg)
#define SCREEN_ERROR(Msg)							ScreenDebugMessageImpl(FColor::Red, 8.0f, Msg)
#define SCREEN_SUCCESS(Msg)							ScreenDebugMessageImpl(FColor::Green, 5.0f, Msg)

#define LOG_ERROR(fmt, ...)							UE_LOG(DP_LOG, Error, fmt, ##__VA_ARGS__)
#define LOG_WARNING(fmt, ...)						UE_LOG(DP_LOG, Warning, fmt, ##__VA_ARGS__)
#define LOG_LOG(fmt, ...)							UE_LOG(DP_LOG, Log, fmt, ##__VA_ARGS__)

#define POPUP_MSG(MsgType, Title, Format, ...)		PopupMessageImpl(MsgType, FString::Printf(Format, ##__VA_ARGS__), Title)
#define POPUP_LOG(Format, ...)						POPUP_MSG(EAppMsgType::Ok,        TEXT("Log"),      Format, ##__VA_ARGS__)
#define POPUP_WARN(Format, ...)						POPUP_MSG(EAppMsgType::Ok,        TEXT("Warning"),  Format, ##__VA_ARGS__)
#define POPUP_ERROR(Format, ...)					POPUP_MSG(EAppMsgType::Ok,        TEXT("Error"),    Format, ##__VA_ARGS__)

#define NOTIFY_MSG(Color, Duration, Format, ...)	NotificationMessageImpl(Color, Duration, FString::Printf(Format, ##__VA_ARGS__))
#define NOTIFY_LOG(...)								NOTIFY_MSG(FColor::White,    3.0f, __VA_ARGS__)
#define NOTIFY_WARN(...)							NOTIFY_MSG(FColor::Orange,   5.0f, __VA_ARGS__)
#define NOTIFY_ERROR(...)							NOTIFY_MSG(FColor::Red,      8.0f, __VA_ARGS__)
#define NOTIFY_SUCCESS(...)							NOTIFY_MSG(FColor::Green,    3.0f, __VA_ARGS__)
