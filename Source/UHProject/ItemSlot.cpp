#include "ItemSlot.h"

UItemSlot::UItemSlot()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UItemSlot::BeginPlay()
{
	Super::BeginPlay();
	
}

void UItemSlot::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

