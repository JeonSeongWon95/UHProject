#include "PickUpItem.h"
#include "UHProjectCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"


void APickUpItem::Interaction_Implementation()
{
	mPlayerCharacter->EquipItem(this);
}

void APickUpItem::DisableLineTraceCollisionAndPhyiscs()
{
	LineTraceCollision->SetActive(false);
	ItemMesh->SetSimulatePhysics(false);
	ItemMesh->SetEnableGravity(false);

	LineTraceCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

void APickUpItem::EnableLineTraceCollisionAndPhyiscs()
{
	LineTraceCollision->SetActive(true);
	ItemMesh->SetSimulatePhysics(true);
	ItemMesh->SetEnableGravity(true);

	LineTraceCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}
