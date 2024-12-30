#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "PickUpItem.generated.h"


UCLASS()
class UHPROJECT_API APickUpItem : public AItem
{
	GENERATED_BODY()

public:
	virtual void Interaction_Implementation() override;

	UFUNCTION()
	void DisableLineTraceCollisionAndPhyiscs();

	UFUNCTION()
	void EnableLineTraceCollisionAndPhyiscs();
	
};
