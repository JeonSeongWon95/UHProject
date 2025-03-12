#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.h"
#include "UHProjectPlayerCar.generated.h"

UCLASS()
class UHPROJECT_API AUHProjectPlayerCar : public AItem
{
    GENERATED_BODY()

public:
    AUHProjectPlayerCar();

    virtual void Interaction_Implementation() override;

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<class USceneComponent> mDriverSeat;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<class USplineComponent> mDriveLine;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float mDriveSpeed = 0.2f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<class USoundBase*> mCarSounds;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<class UAudioComponent> mSpawnedSound;


public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<AActor> mSplineActor;

    UFUNCTION()
    void SetMeshCollision(bool IsUse);

    UFUNCTION(BlueprintImplementableEvent, Category = "Custom")
    void BlueprintDrive();

    UFUNCTION()
    void Drive();

    UFUNCTION(BlueprintCallable, Category = "Custom")
    void FinishDrive();

    UFUNCTION()
    FVector GetDriverLocation()
    {
        return mDriverSeat->GetComponentLocation();
    }

};
