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

    UFUNCTION()
    virtual void StartTalk();

    UFUNCTION()
    virtual void DialogActionA();

    UFUNCTION()
    virtual void DialogActionB();

    UFUNCTION()
    virtual void DialogActionC();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<class UDataTable> mDialogDataTable;

protected:
	UPROPERTY()
	TObjectPtr<class UDialogComponent> mDialogComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<class UCameraComponent> mNPCCamera;

	virtual void BeginPlay() override;

	virtual void Interaction_Implementation() override;


};
