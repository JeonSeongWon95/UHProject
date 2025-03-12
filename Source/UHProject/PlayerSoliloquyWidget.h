#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerSoliloquyWidget.generated.h"


UCLASS()
class UHPROJECT_API UPlayerSoliloquyWidget : public UUserWidget
{
	GENERATED_BODY()

public:

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<class UTextBlock> mText;

    UFUNCTION()
    void SetText(FText NewText);
	
};
