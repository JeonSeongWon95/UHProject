#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NoteWidget.generated.h"


UCLASS()
class UHPROJECT_API UNoteWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<class UBackgroundBlur> mBlur;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<class UTextBlock> mText;
	
};
