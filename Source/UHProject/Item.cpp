#include "Item.h"
#include "UHProjectCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"


AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	RootComponent = ItemMesh;

	LineTraceCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("LineTraceCollision"));
	LineTraceCollision->SetupAttachment(ItemMesh);
	LineTraceCollision->OnComponentBeginOverlap.AddDynamic(this, &AItem::LineTraceCollisionOverlap);
	LineTraceCollision->OnComponentEndOverlap.AddDynamic(this, &AItem::LineTraceCollisionEndOverlap);
}

void AItem::DisableLineTraceCollisionAndPhyiscs()
{
	LineTraceCollision->SetActive(false);
	ItemMesh->SetSimulatePhysics(false);
	ItemMesh->SetEnableGravity(false);

	LineTraceCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

void AItem::EnableLineTraceCollisionAndPhyiscs()
{
	LineTraceCollision->SetActive(true);
	ItemMesh->SetSimulatePhysics(true);
	ItemMesh->SetEnableGravity(true);

	LineTraceCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void AItem::BeginPlay()
{
	Super::BeginPlay();

	mPlayerCharacter = Cast<AUHProjectCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
}

void AItem::Interaction_Implementation()
{

}

void AItem::LineTraceCollisionOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AUHProjectCharacter* Player = Cast<AUHProjectCharacter>(OtherActor);

	if (Player)
	{
		Player->StartLineTrace();
	}
}

void AItem::LineTraceCollisionEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AUHProjectCharacter* Player = Cast<AUHProjectCharacter>(OtherActor);

	if (Player)
	{
		Player->StopLineTrace();
	}
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

