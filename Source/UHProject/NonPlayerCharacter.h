#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "NonPlayerCharacter.generated.h"

UCLASS()
class UHPROJECT_API ANonPlayerCharacter : public AItem
{
	GENERATED_BODY()

public:
	ANonPlayerCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsMove = false;

	UFUNCTION()
	virtual void EndTalk();

protected:
	UPROPERTY()
	TObjectPtr<class UDialogComponent> mDialogComponent;

	virtual void BeginPlay() override;

	virtual void Interaction_Implementation() override;


};
