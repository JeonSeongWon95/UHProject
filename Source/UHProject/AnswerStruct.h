#pragma once

#include "CoreMinimal.h"
#include "AnswerStruct.generated.h" 


USTRUCT(BlueprintType)
struct FAnswerStruct
{
	GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
    TObjectPtr<class UTextBlock> Texts;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
    TObjectPtr<class UButton> Button;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
    FName AnswerNextRowName;

};

