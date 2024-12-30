#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DialogComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UHPROJECT_API UDialogComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDialogComponent();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UDialogueWidget> mDialogueWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UDialogueWidget> mDialogueWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class ANonPlayerCharacter> mNonPlayerCharacter;

	UPROPERTY()
	FName CurrentDataTableRowName;

	UPROPERTY()
	FName LastDataTableRowName;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UDataTable> mDialogDataTable;

	UFUNCTION()
	void SetSpeakName(const FText& Name);

	UFUNCTION()
	void StartTalk();

	UFUNCTION()
	void SetNextRowName(const FName& NewName);

	UFUNCTION()
	void EndTalk();
		
};
