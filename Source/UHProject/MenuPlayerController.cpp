#include "MenuPlayerController.h"

AMenuPlayerController::AMenuPlayerController()
{
    mDuration = 5.0f;
}

void AMenuPlayerController::FadeOut()
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

void AMenuPlayerController::FadeIn()
{
    PlayerCameraManager->StartCameraFade(1.f, 0.f, mDuration, FLinearColor::Black, false, true);
}
