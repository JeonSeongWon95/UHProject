#include "UHProjectPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "UHProjectGameState.h"

void AUHProjectPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = 
        ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
}

void AUHProjectPlayerController::FadeOutAndNextDay()
{
    PlayerCameraManager->StartCameraFade(0.f, 1.f, mDuration, FLinearColor::Black, false, true);
    AUHProjectGameState* GameState = GetWorld()->GetGameState<AUHProjectGameState>();
    GetWorld()->GetTimerManager().SetTimer(TimeHandle,GameState, &AUHProjectGameState::NextDay, mDuration, false);
}

void AUHProjectPlayerController::FadeOut()
{
    PlayerCameraManager->StartCameraFade(0.f, 1.f, mDuration, FLinearColor::Black, false, true);
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
