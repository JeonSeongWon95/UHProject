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
	TObjectPtr<UStaticMeshComponent> CarMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UBoxComponent> DoorCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UBoxComponent> CarCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UBoxComponent> LineTraceCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector DriverSeatLocation;

	UFUNCTION()
	void LineTraceCollisionOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void LineTraceCollisionEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


public:	
	virtual void Tick(float DeltaTime) override;

};
