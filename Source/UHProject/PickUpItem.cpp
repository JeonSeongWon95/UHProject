#include "PickUpItem.h"
#include "UHProjectCharacter.h"

void APickUpItem::Interaction_Implementation()
{
	mPlayerCharacter->EquipItem(this);
}
