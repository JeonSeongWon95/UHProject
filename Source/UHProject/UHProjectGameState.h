#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "UHProjectGameState.generated.h"

UENUM(BlueprintType)
enum class Days : uint8
{
	Monday UMETA(DisplayName = "Monday"),
	Tuesday UMETA(DisplayName = "Tuesday"),
	Wednesday UMETA(DisplayName = "Wednesday"),
	Thursday UMETA(DisplayName = "Thursday"),
	Friday UMETA(DisplayName = "Friday"),
	Saturday UMETA(DisplayName = "Saturday"),
	Sunday UMETA(DisplayName = "Sunday"),
};

UCLASS()
class UHPROJECT_API AUHProjectGameState : public AGameStateBase
{
	GENERATED_BODY()

private:
	Days CurrentDay;

public:
	Days GetCurrentDay() 
	{
		return CurrentDay;
	}

	void NextDay() 
	{
		CurrentDay = static_cast<Days>(static_cast<int>(CurrentDay) + 1);

		if (CurrentDay == Days::Sunday)
		{
			CurrentDay = Days::Sunday;
		}
	}
	
};
