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
		mPlayerCharacter->SetActorLocation(DriverSeatLocation);
		mPlayerCharacter->mPlayerState->CanMove = false;
		mPlayerCharacter->mPlayerState->CanLook = true;
	}
	else 
	{
		FVector TargetLocation = GetActorLocation().RightVector + 100;
		mPlayerCharacter->SetActorLocation(TargetLocation);
		mPlayerCharacter->mPlayerState->CanMove = true;
		mPlayerCharacter->mPlayerState->CanLook = true;
	}
}

AUHProjectPlayerCar::AUHProjectPlayerCar()
{
	PrimaryActorTick.bCanEverTick = true;

	Name = "My Car";

	CarMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CarMesh"));
	RootComponent = CarMesh;

	DoorCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("DoorCollision"));
	DoorCollision->SetupAttachment(CarMesh);

	CarCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("CarCollision"));
	CarCollision->SetupAttachment(CarMesh);
	CarCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	LineTraceCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("LineTraceCollision"));
	LineTraceCollision->SetupAttachment(CarMesh);
	LineTraceCollision->OnComponentBeginOverlap.AddDynamic(this, &AUHProjectPlayerCar::LineTraceCollisionOverlap);
	LineTraceCollision->OnComponentEndOverlap.AddDynamic(this, &AUHProjectPlayerCar::LineTraceCollisionEndOverlap);
}

void AUHProjectPlayerCar::BeginPlay()
{
	Super::BeginPlay();
	
	mPlayerCharacter = Cast<AUHProjectCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
}

void AUHProjectPlayerCar::LineTraceCollisionOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AUHProjectCharacter* Player = Cast<AUHProjectCharacter>(OtherActor);

	if (Player) 
	{
		Player->StartLineTrace();
	}
}

void AUHProjectPlayerCar::LineTraceCollisionEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AUHProjectCharacter* Player = Cast<AUHProjectCharacter>(OtherActor);

	if (Player)
	{
		Player->StopLineTrace();
	}
}

void AUHProjectPlayerCar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

