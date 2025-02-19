// Copyright Epic Games, Inc. All Rights Reserved.

#include "UHProjectGameMode.h"
#include "UHProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUHProjectGameMode::AUHProjectGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
