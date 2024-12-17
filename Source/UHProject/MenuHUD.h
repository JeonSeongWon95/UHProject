
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<class UTitleWidget> mTitleWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<class UStartStoryDescriptionWidget> mSSDWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TObjectPtr<class UTitleWidget> mTitleWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TObjectPtr<class UStartStoryDescriptionWidget> mSSDWidget;

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
	FTimerHandle mTypingTimerHandle;


	
};
