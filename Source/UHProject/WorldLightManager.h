#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WorldLightManager.generated.h"

UCLASS()
class UHPROJECT_API AWorldLightManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AWorldLightManager();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

    UPROPERTY()
    TArray<AActor*> Lights;

    UFUNCTION()
    void LightOFF(int32 LightIndex);

    UFUNCTION()
    void LightON(int32 LightIndex);

};
