// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UHProjectPlayerController.generated.h"

class UInputMappingContext;

UCLASS()
class UHPROJECT_API AUHProjectPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
    UFUNCTION()
    void FadeOutAndNextDay();

	UFUNCTION()
	void FadeOut();

	UFUNCTION()
	void FadeIn();

	UFUNCTION()
	void ShowMouseCursor();

	UFUNCTION()
	void HideMouseCursor();
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	UPROPERTY()
	float mDuration = 5.0f;

    FTimerHandle TimeHandle;

	virtual void BeginPlay() override;

};
