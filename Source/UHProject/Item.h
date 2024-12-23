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

	UFUNCTION()
	virtual FString GetObjectName()
	{
		return Name;
	};


protected:
	virtual void BeginPlay() override;

	virtual void Interaction_Implementation() override;

	UPROPERTY()
	TObjectPtr<class AUHProjectCharacter> mPlayerCharacter;
	
	UPROPERTY()
	FString Name;


public:	
	virtual void Tick(float DeltaTime) override;

};
