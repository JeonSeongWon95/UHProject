#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "UHProjectGameState.generated.h"

UENUM(BlueprintType)
enum class EDays : uint8
{
    None UMETA(DisplayName = "None"),
	Monday UMETA(DisplayName = "Monday"),
	Tuesday UMETA(DisplayName = "Tuesday"),
	Wednesday UMETA(DisplayName = "Wednesday"),
	Thursday UMETA(DisplayName = "Thursday"),
	Friday UMETA(DisplayName = "Friday"),
	Saturday UMETA(DisplayName = "Saturday"),
	Sunday UMETA(DisplayName = "Sunday"),
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEventDispatcher_GameDayChange, EDays, NewDay);

UCLASS()
class UHPROJECT_API AUHProjectGameState : public AGameStateBase
{
	GENERATED_BODY()

private:

    virtual void BeginPlay() override;

protected:
    UPROPERTY()
    EDays CurrentDay = EDays::None;

public:
    EDays GetCurrentDay()
	{
		return CurrentDay;
	}

    UPROPERTY()
    FEventDispatcher_GameDayChange EventDispatcherGameDayChange;

	void NextDay() 
	{
		CurrentDay = static_cast<EDays>(static_cast<int>(CurrentDay) + 1);

		if (CurrentDay == EDays::Sunday)
		{
			CurrentDay = EDays::Sunday;
		}

        if (EventDispatcherGameDayChange.IsBound()) 
        {
            EventDispatcherGameDayChange.Broadcast(CurrentDay);
        }
	}
	
};
