#include "WorldBackGroundMusicManager.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"


AWorldBackGroundMusicManager::AWorldBackGroundMusicManager()
{
	PrimaryActorTick.bCanEverTick = true;

}


void AWorldBackGroundMusicManager::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWorldBackGroundMusicManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWorldBackGroundMusicManager::PlayMusic()
{
    IsPlayedBGM = true;
    CurrentPlayedBGM = UGameplayStatics::SpawnSound2D(GetWorld(), BackGroundMusics[static_cast<int>(CurrentBGMType)]);
}

void AWorldBackGroundMusicManager::SetMusic(EBGMType NewType)
{
    if (IsPlayedBGM)
    {
        CurrentPlayedBGM->Stop();
        IsPlayedBGM = false;
    }


    CurrentBGMType = NewType;
}

