#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UHProjectGameState.h"
#include "UHProjectGameMode.generated.h"

UCLASS(minimalapi)
class AUHProjectGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AUHProjectGameMode();

    virtual void BeginPlay() override;

    UFUNCTION()
    void SettingAllObjects(EDays NewDay);

    UFUNCTION()
    void ResetCharacter();

    UPROPERTY()
    TObjectPtr<class AUHPlayerState> mPlayerState;

    UPROPERTY()
    TObjectPtr<class AUHProjectCharacter> mPlayerCharacter;

    UPROPERTY()
    TObjectPtr<class AUHProjectPlayerCar> mPlayerCar;

    UPROPERTY()
    TObjectPtr<class AUHProjectPlayerController> mPlayerController;

    UPROPERTY()
    TObjectPtr<class AUHProjectGameState> mGameState;


    
};



