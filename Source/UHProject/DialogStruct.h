#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "DialogStruct.generated.h" 

USTRUCT(BlueprintType)
struct FDialogStruct : public FTableRowBase
{
	GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
    FText Dialog;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
    TArray<FText> Answers;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
    TArray<FName> NextRows;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
    int32 AnswersCount;

};

