#include "Item.h"


AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AItem::BeginPlay()
{
	Super::BeginPlay();
}

void AItem::Interaction_Implementation()
{

}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

