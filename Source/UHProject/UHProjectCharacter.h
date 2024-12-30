#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "UHProjectCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AUHProjectCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;
	
public:
	AUHProjectCharacter();

protected:
	virtual void BeginPlay();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UItemSlot> mItemSlot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractionAction;

	UPROPERTY()
	TObjectPtr<class AUHPlayerState> mPlayerState;

	UPROPERTY()
	TObjectPtr<class AUHProjectPlayerController> mPlayerController;

	UPROPERTY()
	TObjectPtr<class AItem> mCurrentHitItem;

	UPROPERTY()
	TObjectPtr<APickUpItem> mEquipItem;

	UPROPERTY()
	float mLength;

	FTimerHandle LineTraceTimer;

	UFUNCTION()
	void LineTrace();

	UFUNCTION()
	void StartLineTrace();

	UFUNCTION()
	void StopLineTrace();
	
	UFUNCTION()
	void EquipItem(APickUpItem* SeletedItem);

	UFUNCTION()
	void UnEquipItem();

protected:
	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	void Interaction(const FInputActionValue& Value);

	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	UPROPERTY()
	TObjectPtr<class AMenuHUD> mHUD;

public:
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};

