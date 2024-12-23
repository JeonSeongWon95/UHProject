#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PressEWidget.generated.h"


UCLASS()
class UHPROJECT_API UPressEWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UTextBlock> ObjectName;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UTextBlock> PressEKey;

	UFUNCTION()
	void SetObjectName(FString NewName);

	UFUNCTION()
	void ShowPressEKeyText();

	UFUNCTION()
	void HidePressEKeyText();
};
