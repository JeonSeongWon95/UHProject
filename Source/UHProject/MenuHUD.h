
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MenuHUD.generated.h"


UCLASS()
class UHPROJECT_API AMenuHUD : public AHUD
{
	GENERATED_BODY()

public:
	AMenuHUD();

	UFUNCTION()
	void StartTyping(const FString& TypingText, float TypingSpeed);

	UFUNCTION()
	void UpdateTyping();

	UFUNCTION()
	void BeginPlay() override;

	UFUNCTION()
	void PrintCurrentDay();

	UFUNCTION()
	void RemoveCurrentDayWidget();

	UFUNCTION()
	void SetAndShowObjectPopUp(FString Name, bool ShowPressEKey);

	UFUNCTION()
	void RemoveObjectPopUp();

    UFUNCTION()
    void StartSoliloquy(FText NewText);

    UFUNCTION()
    void FinishedSoliloquy();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<class UTitleWidget> mTitleWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<class UStartStoryDescriptionWidget> mSSDWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TObjectPtr<class UTitleWidget> mTitleWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TObjectPtr<class UStartStoryDescriptionWidget> mSSDWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<class UCurrentDayPrintWidget> mDayPrintWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TObjectPtr<class UCurrentDayPrintWidget> mDayPrintWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<class UPressEWidget> mPressEWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TObjectPtr<class UPressEWidget> mPressEWidget;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
    TSubclassOf<class UPlayerSoliloquyWidget> mSoliloquyWidgetClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
    TObjectPtr<class UPlayerSoliloquyWidget> mSoliloquyWidget;

private:

	UPROPERTY()
	FString mTargetText;

	UPROPERTY()
	FString mCurrentText;

	UPROPERTY()
	int32 mCurrentIndex;

	UPROPERTY()
	float mSpeed;

	UPROPERTY()
	TObjectPtr<class AUHProjectPlayerController> mPlayerController;

    UPROPERTY()
    TObjectPtr<class AUHProjectCharacter> mPlayerCharacter;

	UPROPERTY()
	FTimerHandle mTypingTimerHandle;

    UPROPERTY()
    FTimerHandle mSoliloquyTimerHandle;

	UPROPERTY()
	TObjectPtr<class AUHPlayerState> mPlayerState;

	UPROPERTY()
	float mStayTimer;

	UPROPERTY()
	TObjectPtr<class AUHProjectGameState> mGameState;

	UPROPERTY()
	FTimerHandle mCurrentDayPrintTimer;


	
};
