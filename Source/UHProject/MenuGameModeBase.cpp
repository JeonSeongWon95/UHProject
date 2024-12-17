// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuGameModeBase.h"
#include "MenuHUD.h"
#include "UHProjectPlayerController.h"
#include "UHProjectCharacter.h"
#include "UHPlayerState.h"

AMenuGameModeBase::AMenuGameModeBase()
{
	DefaultPawnClass = AUHProjectCharacter::StaticClass();
	HUDClass = AMenuHUD::StaticClass();
	PlayerControllerClass = AUHProjectPlayerController::StaticClass();
	PlayerStateClass = AUHPlayerState::StaticClass();
}
