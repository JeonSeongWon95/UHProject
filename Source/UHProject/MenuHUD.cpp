#include "MenuHUD.h"
#include "TitleWidget.h"
#include "StartStoryDescriptionWidget.h"
#include "UHProjectPlayerController.h"

AMenuHUD::AMenuHUD()
{
	static ConstructorHelpers::FClassFinder<UTitleWidget> Title(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/SeongWon/UI/Title/BP_TitleWidget.BP_TitleWidget_C'"));
	static ConstructorHelpers::FClassFinder<UStartStoryDescriptionWidget> SSD(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/SeongWon/UI/Title/BP_StartStoryDescriptionWidget.BP_StartStoryDescriptionWidget_C'"));

	if (Title.Succeeded())
	{
		mTitleWidgetClass = Title.Class;
	}

	if (SSD.Succeeded())
	{
		mSSDWidgetClass = SSD.Class;
	}
}

void AMenuHUD::StartTyping(const FString& TypingText, float TypingSpeed)
{
	mTitleWidget->RemoveFromViewport();
	mSSDWidget->AddToViewport();

	mTargetText = TypingText;
	mSpeed = TypingSpeed;
	mCurrentIndex = 0;
	mCurrentText.Empty();

	GetWorld()->GetTimerManager().SetTimer(mTypingTimerHandle, this, &AMenuHUD::UpdateTyping, mSpeed, true);

}

void AMenuHUD::UpdateTyping()
{
	if (mCurrentIndex < mTargetText.Len())
	{

		mCurrentText.AppendChar(mTargetText[mCurrentIndex]);
		mCurrentIndex++;

		mSSDWidget->SetText(FText::FromString(mCurrentText));
		

	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(mTypingTimerHandle);
		mSSDWidget->RemoveFromParent();
		mPlayerController->FadeIn();
	}

}

void AMenuHUD::BeginPlay()
{
	mTitleWidget = Cast<UTitleWidget>(CreateWidget(GetWorld(), mTitleWidgetClass));
	mTitleWidget->AddToViewport();

	mSSDWidget = Cast<UStartStoryDescriptionWidget>(CreateWidget(GetWorld(), mSSDWidgetClass));
	mPlayerController = Cast<AUHProjectPlayerController>(GetWorld()->GetFirstPlayerController());
	
}
