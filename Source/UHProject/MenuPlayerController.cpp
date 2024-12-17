#include "MenuPlayerController.h"

AMenuPlayerController::AMenuPlayerController()
{
    mDuration = 5.0f;
}

void AMenuPlayerController::FadeOut()
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

void AMenuPlayerController::FadeIn()
{
    PlayerCameraManager->StartCameraFade(1.f, 0.f, mDuration, FLinearColor::Black, false, true);
}
