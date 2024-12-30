#include "NonPlayerCharacter.h"
#include "DialogComponent.h"
#include "UHProjectCharacter.h"
#include "UHPlayerState.h"
#include "UHProjectplayerController.h"

ANonPlayerCharacter::ANonPlayerCharacter()
{
	mDialogComponent = CreateDefaultSubobject<UDialogComponent>(TEXT("Dialog Component"));
}

void ANonPlayerCharacter::EndTalk()
{
	mPlayerCharacter->mPlayerState->CanMove = true;
	mPlayerCharacter->mPlayerState->CanLook = true;
	mPlayerCharacter->mPlayerController->HideMouseCursor();
}

void ANonPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	mDialogComponent->SetSpeakName(FText::FromString(Name));
}

void ANonPlayerCharacter::Interaction_Implementation()
{
	mPlayerCharacter->mPlayerState->CanMove = false;
	mPlayerCharacter->mPlayerState->CanLook = false;
	mPlayerCharacter->mPlayerController->ShowMouseCursor();
	mDialogComponent->StartTalk();
}
