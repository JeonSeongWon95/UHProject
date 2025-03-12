
#pragma once

#include "CoreMinimal.h"
#include "NonPlayerCharacter.h"
#include "NonPlayerCharacterEmployee.generated.h"


UCLASS()
class UHPROJECT_API ANonPlayerCharacterEmployee : public ANonPlayerCharacter
{
	GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<AActor> mFood;

    virtual void DialogActionA() override;
                                        
    virtual void DialogActionB() override;
                   
    virtual void DialogActionC() override;

    virtual void BeginPlay() override;

    FTimerHandle FoodTimerHandle;

protected:
    void ShowFood();

    void HideFood();

};
