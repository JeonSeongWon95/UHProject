#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MenuPlayerController.generated.h"


UCLASS()
class UHPROJECT_API AMenuPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMenuPlayerController();

	UFUNCTION()
	void FadeOut();

	UFUNCTION()
	void FadeIn();

private:
	UPROPERTY()
	float mDuration;
	
};
