#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectInterface.h"
#include "Item.generated.h"

UCLASS()
class UHPROJECT_API AItem : public AActor , public IObjectInterface
{
	GENERATED_BODY()
	
public:	
	AItem();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	int ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

protected:
	virtual void BeginPlay() override;

	virtual void Interaction_Implementation() override;

	UPROPERTY()
	TObjectPtr<class AUHProjectCharacter> mPlayerCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> ItemMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UBoxComponent> LineTraceCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UBoxComponent> ObjectCollision;

	UFUNCTION()
	void LineTraceCollisionOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void LineTraceCollisionEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
