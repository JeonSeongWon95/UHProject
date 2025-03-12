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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UItemSlot> mItemSlot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractionAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* ToggleAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* SprintAction;

	UPROPERTY()
	TObjectPtr<class AUHPlayerState> mPlayerState;

	UPROPERTY()
	TObjectPtr<class AUHProjectPlayerController> mPlayerController;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<class AUHProjectPlayerCar> mPlayerCar;

	UPROPERTY()
	TObjectPtr<class AItem> mCurrentHitItem;

	UPROPERTY()
	TObjectPtr<APickUpItem> mEquipItem;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<class USpotLightComponent> mFlashLight;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<class USpotLightComponent> mFlashLightInner;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<class USpringArmComponent> mCameraBoom;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<class AWorldBackGroundMusicManager> mWorldBGMManager;

	UPROPERTY()
	float mLength;

	FTimerHandle LineTraceTimer;

    UPROPERTY()
    float FootStepTimer;

    struct FSoliloquyStruct* SoliloquyStruct;

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

    UFUNCTION()
    void GetInTheCar();

    UFUNCTION()
    void GetOutTheCar();

    UFUNCTION()
    void TurnOnOrOFFFlashLight(bool IsTurnOn);

    UFUNCTION()
    void PlayerDriveStart();

    UFUNCTION()
    void ResetCharacter();

    UFUNCTION()
    void Soliloquy();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<class UDataTable> mSoliloquyDataTable;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<class USoundBase> FootStepSound_InSide;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<class USoundBase> FootStepSound_OutSide;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<class USoundBase> FlashLightToggleSound;

    UPROPERTY()
    FName CurrentDataTableRowName;

    UPROPERTY()
    int32 CurrentDataTableIndex;

protected:
	void Move(const FInputActionValue& Value);

    void StopMove(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	void Interaction(const FInputActionValue& Value);

    void ToggleFlashLight(const FInputActionValue& Value);

    void Sprint(const FInputActionValue& Value);

    void StopSprint(const FInputActionValue& Value);

	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	UPROPERTY()
	TObjectPtr<class AMenuHUD> mHUD;

    UFUNCTION()
    void TraceFootStep();

public:
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};

