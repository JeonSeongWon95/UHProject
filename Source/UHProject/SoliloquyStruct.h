#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SoliloquyStruct.generated.h" 

USTRUCT(BlueprintType)
struct FSoliloquyStruct : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
    FString Soliloquy;
};