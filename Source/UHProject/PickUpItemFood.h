#pragma once

#include "CoreMinimal.h"
#include "PickUpItem.h"
#include "PickUpItemFood.generated.h"

UCLASS()
class UHPROJECT_API APickUpItemFood : public APickUpItem
{
	GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere)
    TArray<UMaterialInterface*> MaterialArray;

    UFUNCTION()
    void SetUdon();

    UFUNCTION()
    void SetRamen();
	
};
