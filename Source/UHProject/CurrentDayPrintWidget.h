#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CurrentDayPrintWidget.generated.h"


UCLASS()
class UHPROJECT_API UCurrentDayPrintWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UTextBlock> CurrentDay;

	UFUNCTION()
	void SetText(FText NewText);
	
};
