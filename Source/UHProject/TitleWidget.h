#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TitleWidget.generated.h"


UCLASS()
class UHPROJECT_API UTitleWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> ButtonGameStart;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> ButtonOption;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> ButtonQuit;

	UPROPERTY()
	TObjectPtr<class AUHProjectPlayerController> mPlayerController;

	UPROPERTY()
	FTimerHandle mStartTypingTimerHandle;

public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void ClickedGameStart();

	UFUNCTION(BlueprintCallable)
	void ClickedOption();

	UFUNCTION(BlueprintCallable)
	void ClickedQuit();

	UFUNCTION(BlueprintCallable)
	void CallStartTyping();

	
};
