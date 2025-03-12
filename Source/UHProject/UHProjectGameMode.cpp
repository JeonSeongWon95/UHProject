#include "UHProjectGameMode.h"
#include "UHProjectCharacter.h"
#include "UHProjectGameState.h"
#include "UHProjectPlayerCar.h"
#include "UHPlayerState.h"
#include "UHProjectPlayerController.h"

AUHProjectGameMode::AUHProjectGameMode()
	: Super()
{
	DefaultPawnClass = AUHProjectCharacter::StaticClass();
    PlayerStateClass = AUHPlayerState::StaticClass();
    GameStateClass = AUHProjectGameState::StaticClass();
    PlayerControllerClass = AUHProjectPlayerController::StaticClass();
}

void AUHProjectGameMode::BeginPlay()
{
    Super::BeginPlay();

    mGameState = GetGameState<AUHProjectGameState>();
    mGameState->EventDispatcherGameDayChange.AddDynamic(this, &AUHProjectGameMode::SettingAllObjects);
    
}

void AUHProjectGameMode::SettingAllObjects(EDays NewDay)
{

    switch (NewDay)
    {
    case EDays::Monday:
        ResetCharacter();
        break;
    case EDays::Tuesday:
        break;
    case EDays::Wednesday:
        break;
    case EDays::Thursday:
        break;
    case EDays::Friday:
        break;
    case EDays::Saturday:
        break;
    case EDays::Sunday:
        break;
    default:
        break;
    }
}

void AUHProjectGameMode::ResetCharacter()
{
    mPlayerCharacter->GetInTheCar();
    mPlayerCharacter->StopLineTrace();
}
