#include "NonPlayerCharacter.h"
#include "DialogComponent.h"
#include "UHProjectCharacter.h"
#include "UHPlayerState.h"
#include "UHProjectplayerController.h"
#include "Camera/CameraComponent.h"

ANonPlayerCharacter::ANonPlayerCharacter()
{
	mDialogComponent = CreateDefaultSubobject<UDialogComponent>(TEXT("Dialog Component"));
    mNPCCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    mNPCCamera->SetupAttachment(RootComponent);
}

void ANonPlayerCharacter::EndTalk()
{
	mPlayerCharacter->mPlayerState->CanMove = true;
	mPlayerCharacter->mPlayerState->CanLook = true;
	mPlayerCharacter->mPlayerController->HideMouseCursor();
    mPlayerCharacter->mPlayerController->SetViewTarget(mPlayerCharacter);
}

void ANonPlayerCharacter::StartTalk()
{
    mPlayerCharacter->mPlayerState->CanMove = false;
    mPlayerCharacter->mPlayerState->CanLook = false;
    mPlayerCharacter->mPlayerController->ShowMouseCursor();
    mPlayerCharacter->mPlayerController->SetViewTarget(this);
    mPlayerCharacter->StopLineTrace();
    mDialogComponent->StartTalk();
}

void ANonPlayerCharacter::DialogActionA()
{

}

void ANonPlayerCharacter::DialogActionB()
{

}

void ANonPlayerCharacter::DialogActionC()
{

}

void ANonPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	mDialogComponent->SetSpeakName(FText::FromString(Name));
    mDialogComponent->SetDialogDataTable(mDialogDataTable);
}

void ANonPlayerCharacter::Interaction_Implementation()
{
    StartTalk();
}
