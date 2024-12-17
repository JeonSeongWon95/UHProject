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
        0.f,              // From Alpha (0: ����)
        1.f,              // To Alpha (1: ������)
        mDuration,         // ���̵� ���� �ð�
        FLinearColor::Black, // ���̵� ���� (��: FLinearColor::Black)
        false,            // ShouldFadeAudio (����� ���̵� ����)
        true              // HoldWhenFinished (�Ϸ� �� ���� ����)
    );

}

void AUHProjectPlayerController::FadeIn()
{
    PlayerCameraManager->StartCameraFade(1.f, 0.f, mDuration, FLinearColor::Black, false, true);
}