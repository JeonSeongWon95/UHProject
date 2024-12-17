#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "UHPlayerState.generated.h"


UCLASS()
class UHPROJECT_API AUHPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	UPROPERTY()
	bool IsLineTraceOn = false;

	UPROPERTY()
	bool CanMove = false;

	UPROPERTY()
	bool CanLook = false;


	
};
