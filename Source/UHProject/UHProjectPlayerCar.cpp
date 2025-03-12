#include "UHProjectPlayerCar.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UHProjectCharacter.h"
#include "UHPlayerState.h"
#include "Components/SplineComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

void AUHProjectPlayerCar::Interaction_Implementation()
{
	Super::Interaction_Implementation();

	if (mPlayerCharacter->mPlayerState->IsInTheCar)
	{
        mPlayerCharacter->GetOutTheCar();
	}
	else 
	{
        mPlayerCharacter->GetInTheCar();
	}
}

AUHProjectPlayerCar::AUHProjectPlayerCar()
{
    mDriverSeat = CreateDefaultSubobject<USceneComponent>(TEXT("DriverSeat"));
    mDriverSeat->SetupAttachment(ItemMesh);

	PrimaryActorTick.bCanEverTick = true;

    if (mSplineActor != nullptr)
    {
        mDriveLine = mSplineActor->GetComponentByClass<USplineComponent>();
    }

	Name = "My Car";
}

void AUHProjectPlayerCar::BeginPlay()
{
	Super::BeginPlay();
}

void AUHProjectPlayerCar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUHProjectPlayerCar::SetMeshCollision(bool IsUse)
{
    if (IsUse) 
    {
        ItemMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    }
    else 
    {
        ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }
}

void AUHProjectPlayerCar::Drive()
{
    BlueprintDrive();

    if (mCarSounds.Num() > 0)
    {
        mSpawnedSound = UGameplayStatics::SpawnSound2D(GetWorld(), mCarSounds[0]);
    }
}

void AUHProjectPlayerCar::FinishDrive()
{
    mPlayerCharacter->ResetCharacter();

    if (mSpawnedSound->IsPlaying()) 
    {
        mSpawnedSound->Stop();
    }

    UGameplayStatics::PlaySound2D(GetWorld(), mCarSounds[1]);

    mPlayerCharacter->Soliloquy();
}

