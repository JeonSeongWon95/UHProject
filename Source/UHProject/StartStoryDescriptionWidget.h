#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StartStoryDescriptionWidget.generated.h"


UCLASS()
class UHPROJECT_API UStartStoryDescriptionWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UTextBlock> DescriptionText;

	UFUNCTION()
	void SetText(FText NewText);
};
