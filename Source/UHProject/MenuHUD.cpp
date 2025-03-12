#include "MenuHUD.h"
#include "TitleWidget.h"
#include "StartStoryDescriptionWidget.h"
#include "UHProjectPlayerController.h"
#include "UHPlayerState.h"
#include "UHProjectGameState.h"
#include "CurrentDayPrintWidget.h"
#include "PressEWidget.h"
#include "UHProjectCharacter.h"
#include "PlayerSoliloquyWidget.h"

AMenuHUD::AMenuHUD()
{
	static ConstructorHelpers::FClassFinder<UTitleWidget> Title(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/SeongWon/UI/Title/BP_TitleWidget.BP_TitleWidget_C'"));
	static ConstructorHelpers::FClassFinder<UStartStoryDescriptionWidget> SSD(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/SeongWon/UI/Title/BP_StartStoryDescriptionWidget.BP_StartStoryDescriptionWidget_C'"));
	static ConstructorHelpers::FClassFinder<UCurrentDayPrintWidget> DFW(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/SeongWon/UI/PrintDayWidget.PrintDayWidget_C'"));
	static ConstructorHelpers::FClassFinder<UPressEWidget> PressWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/SeongWon/UI/PressEWidget.PressEWidget_C'"));
    static ConstructorHelpers::FClassFinder<UPlayerSoliloquyWidget> SoliloquyWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/SeongWon/UI/SoliloquyWidget.SoliloquyWidget_C'"));


	if (Title.Succeeded())
	{
		mTitleWidgetClass = Title.Class;
	}

	if (SSD.Succeeded())
	{
		mSSDWidgetClass = SSD.Class;
	}

	if (DFW.Succeeded())
	{
		mDayPrintWidgetClass = DFW.Class;
	}

	if (PressWidget.Succeeded()) 
	{
		mPressEWidgetClass = PressWidget.Class;
	}

    if (SoliloquyWidget.Succeeded()) 
    {
        mSoliloquyWidgetClass = SoliloquyWidget.Class;
    }

}

void AMenuHUD::StartTyping(const FString& TypingText, float TypingSpeed)
{
	mTitleWidget->RemoveFromParent();
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
		mStayTimer += 1;

		if (mStayTimer > 10.0f)
		{
			mStayTimer = 0;
			GetWorld()->GetTimerManager().ClearTimer(mTypingTimerHandle);
			mSSDWidget->RemoveFromParent();
			PrintCurrentDay();
		}
	}

}

void AMenuHUD::BeginPlay()
{
	mTitleWidget = Cast<UTitleWidget>(CreateWidget(GetWorld(), mTitleWidgetClass));
	mTitleWidget->AddToViewport();

	mSSDWidget = Cast<UStartStoryDescriptionWidget>(CreateWidget(GetWorld(), mSSDWidgetClass));
	mDayPrintWidget = Cast<UCurrentDayPrintWidget>(CreateWidget(GetWorld(), mDayPrintWidgetClass));
	mPressEWidget = Cast<UPressEWidget>(CreateWidget(GetWorld(), mPressEWidgetClass));
    mSoliloquyWidget = Cast<UPlayerSoliloquyWidget>(CreateWidget(GetWorld(), mSoliloquyWidgetClass));

	mPlayerController = Cast<AUHProjectPlayerController>(GetWorld()->GetFirstPlayerController());
	mPlayerState = Cast<AUHPlayerState>(mPlayerController->PlayerState);
    mPlayerCharacter = Cast<AUHProjectCharacter>(mPlayerController->GetPawn());
	mGameState = Cast<AUHProjectGameState>(GetWorld()->GetGameState());

}

void AMenuHUD::PrintCurrentDay()
{
	EDays CurrentDay = mGameState->GetCurrentDay();
	FString Day = "";

	switch (CurrentDay)
	{
	case EDays::Monday:
		Day = "월요일";
		break;
	case EDays::Tuesday:
		Day = "화요일";
		break;
	case EDays::Wednesday:
		Day = "수요일";
		break;
	case EDays::Thursday:
		Day = "목요일";
		break;
	case EDays::Friday:
		Day = "금요일";
		break;
	case EDays::Saturday:
		Day = "토요일";
		break;
	case EDays::Sunday:
		Day = "일요일";
		break;
	default:
		break;
	}

	mDayPrintWidget->SetText(FText::FromString(Day));

	if (!mDayPrintWidget->IsInViewport())
	{
		mDayPrintWidget->AddToViewport();
	}

	GetWorld()->GetTimerManager().SetTimer(mCurrentDayPrintTimer, this, &AMenuHUD::RemoveCurrentDayWidget, 1.0f, true);
}

void AMenuHUD::RemoveCurrentDayWidget()
{
	if (mDayPrintWidget == nullptr)
		return;

	if (mDayPrintWidget->IsInViewport()) 
	{
		mStayTimer += 1;

		if (mStayTimer >= 3.0f) 
		{
			mStayTimer = 0;
			mDayPrintWidget->RemoveFromParent();
			mPlayerController->FadeIn();
		}
		else 
		{
			return;
		}
	}

    mPlayerCharacter->PlayerDriveStart();
	GetWorld()->GetTimerManager().ClearTimer(mCurrentDayPrintTimer);

}

void AMenuHUD::SetAndShowObjectPopUp(FString Name, bool ShowPressEKey)
{
	if (mPressEWidget->IsInViewport()) 
	{
		mPressEWidget->RemoveFromParent();
	}

	mPressEWidget->SetObjectName(Name);

	if (ShowPressEKey) 
	{
		mPressEWidget->ShowPressEKeyText();
	}
	else 
	{
		mPressEWidget->HidePressEKeyText();
	}

	mPressEWidget->AddToViewport();
}

void AMenuHUD::RemoveObjectPopUp()
{
	if (mPressEWidget->IsInViewport())
	{
		mPressEWidget->RemoveFromParent();
	}
}

void AMenuHUD::StartSoliloquy(FText NewText)
{
    if (mSoliloquyWidget == nullptr)
        return;

    mSoliloquyWidget->SetText(NewText);

    if (!mSoliloquyWidget->IsInViewport()) 
    {
        mSoliloquyWidget->AddToViewport();
    }

    GetWorld()->GetTimerManager().SetTimer(mSoliloquyTimerHandle, this, &AMenuHUD::FinishedSoliloquy, 5.0f, true);
}

void AMenuHUD::FinishedSoliloquy()
{
    if (mSoliloquyWidget->IsInViewport()) 
    {
        mSoliloquyWidget->RemoveFromParent();
    }
}
