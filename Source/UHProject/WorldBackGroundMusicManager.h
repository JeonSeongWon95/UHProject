// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WorldBackGroundMusicManager.generated.h"

UENUM()
enum class EBGMType
{
    Rain_In_The_Car,
    Rain_In_The_OutSide,
    Rain_In_The_InSide

};

UCLASS()
class UHPROJECT_API AWorldBackGroundMusicManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AWorldBackGroundMusicManager();

protected:
	virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<class USoundBase*> BackGroundMusics;

    UPROPERTY()
    EBGMType CurrentBGMType = EBGMType::Rain_In_The_Car;

    UPROPERTY()
    TObjectPtr<class UAudioComponent> CurrentPlayedBGM;

    UPROPERTY()
    bool IsPlayedBGM = false;

public:	
	virtual void Tick(float DeltaTime) override;

    UFUNCTION()
    void PlayMusic();

    UFUNCTION()
    void SetMusic(EBGMType NewType);

    UFUNCTION()
    EBGMType GetCurrentBGMType() { return CurrentBGMType; }

};
