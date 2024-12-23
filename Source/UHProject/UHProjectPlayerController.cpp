#include "UHProjectPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"

void AUHProjectPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
}

void AUHProjectPlayerController::FadeOut()
{

    PlayerCameraManager->StartCameraFade(
        0.f,              // From Alpha (0: 투명)
        1.f,              // To Alpha (1: 불투명)
        mDuration,         // 페이드 지속 시간
        FLinearColor::Black, // 페이드 색상 (예: FLinearColor::Black)
        false,            // ShouldFadeAudio (오디오 페이드 여부)
        true              // HoldWhenFinished (완료 후 유지 여부)
    );

}

void AUHProjectPlayerController::FadeIn()
{
    PlayerCameraManager->StartCameraFade(1.f, 0.f, mDuration, FLinearColor::Black, false, true);
}

void AUHProjectPlayerController::ShowMouseCursor()
{
    bShowMouseCursor = true;
}

void AUHProjectPlayerController::HideMouseCursor()
{
    bShowMouseCursor = false;
}
