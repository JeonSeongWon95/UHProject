#include "UHProjectPlayerCar.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UHPlayerState.h"
#include "UHProjectCharacter.h"

void AUHProjectPlayerCar::Interaction_Implementation()
{
	Super::Interaction_Implementation();

	if (mPlayerCharacter->mPlayerState->IsInTheCar)
	{
		mPlayerCharacter->mPlayerState->IsInTheCar = false;
		FVector TargetLocation = GetActorLocation().RightVector + 100;
		mPlayerCharacter->SetActorLocation(TargetLocation);
		mPlayerCharacter->mPlayerState->CanMove = true;
		mPlayerCharacter->mPlayerState->CanLook = true;
	}
	else 
	{
		mPlayerCharacter->mPlayerState->IsInTheCar = true;
		mPlayerCharacter->SetActorLocation(DriverSeatLocation);
		mPlayerCharacter->mPlayerState->CanMove = false;
		mPlayerCharacter->mPlayerState->CanLook = true;
	}
}

AUHProjectPlayerCar::AUHProjectPlayerCar()
{
	PrimaryActorTick.bCanEverTick = true;

	Name = "My Car";

	CarMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CarMesh"));

	ObjectCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("DoorCollision"));
	ObjectCollision->SetupAttachment(CarMesh);

	CarCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("CarCollision"));
	CarCollision->SetupAttachment(CarMesh);
	CarCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AUHProjectPlayerCar::BeginPlay()
{
	Super::BeginPlay();
}

void AUHProjectPlayerCar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

