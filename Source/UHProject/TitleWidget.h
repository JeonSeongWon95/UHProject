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
	TObjectPtr<class UButton> ButtonNewGame;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<class UButton> ButtonLoadGame;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> ButtonOption;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> ButtonQuit;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<class UButton> ButtonReturn;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<class UBorder> ButtonGroup_TitleMenu;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<class UBorder> ButtonGroup_LoadGameMenu;

	UPROPERTY()
	TObjectPtr<class AUHProjectPlayerController> mPlayerController;

	UPROPERTY()
	FTimerHandle mStartTypingTimerHandle;

public:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Desc", meta = (MultiLine = "true"))
	FString StoryDesc;

	UFUNCTION(BlueprintCallable)
	void ClickedNewGame();

	UFUNCTION(BlueprintCallable)
	void ClickedOption();

    UFUNCTION(BlueprintCallable)
    void ClickedLoadGame();

	UFUNCTION(BlueprintCallable)
	void ClickedQuit();

    UFUNCTION(BlueprintCallable)
    void ClickedReturn();

	UFUNCTION(BlueprintCallable)
	void CallStartTyping();

	
};
