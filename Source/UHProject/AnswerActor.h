#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AnswerActor.generated.h" 


UCLASS()
class UHPROJECT_API AAnswerActor : public AActor 
{
	GENERATED_BODY()

public:
    AAnswerActor();

    UFUNCTION()
    void SetTextsAndNextRowName(const FText& NewAnswer, const FName& NextRowName);

    UFUNCTION()
    UButton* GetButton();

    UFUNCTION()
    FName GetNextRowName();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
    TObjectPtr<class UTextBlock> Texts;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
    TObjectPtr<class UButton> Button;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
    FName AnswerNextRowName;

};

