#include "TitleWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "MenuHUD.h"
#include "UHProjectPlayerController.h"
#include "UHProjectGameState.h"
#include "Components/Border.h"

void UTitleWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ButtonNewGame)
	{
        ButtonNewGame->OnClicked.AddDynamic(this, &UTitleWidget::ClickedNewGame);
	}
    if (ButtonLoadGame) 
    {
        ButtonLoadGame->OnClicked.AddDynamic(this, &UTitleWidget::ClickedLoadGame);
    }
    if (ButtonReturn) 
    {
        ButtonReturn->OnClicked.AddDynamic(this, &UTitleWidget::ClickedReturn);
    }
	if (ButtonOption)
	{
		ButtonOption->OnClicked.AddDynamic(this, &UTitleWidget::ClickedOption);
	}
	if (ButtonQuit)
	{
		ButtonQuit->OnClicked.AddDynamic(this, &UTitleWidget::ClickedQuit);
	}

	mPlayerController = Cast<AUHProjectPlayerController>(GetWorld()->GetFirstPlayerController());
	mPlayerController->ShowMouseCursor();
    ButtonGroup_LoadGameMenu->SetVisibility(ESlateVisibility::Hidden);
}

void UTitleWidget::ClickedNewGame()
{
	RemoveFromParent();
    mPlayerController->FadeOutAndNextDay();
	mPlayerController->HideMouseCursor();
	GetWorld()->GetTimerManager().SetTimer(mStartTypingTimerHandle, this, &UTitleWidget::CallStartTyping, 5.0f, false);
    
}

void UTitleWidget::ClickedOption()
{

}

void UTitleWidget::ClickedLoadGame()
{
    ButtonGroup_TitleMenu->SetVisibility(ESlateVisibility::Hidden);
    ButtonGroup_LoadGameMenu->SetVisibility(ESlateVisibility::Visible);
}

void UTitleWidget::ClickedQuit()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}

void UTitleWidget::ClickedReturn()
{
    ButtonGroup_TitleMenu->SetVisibility(ESlateVisibility::Visible);
    ButtonGroup_LoadGameMenu->SetVisibility(ESlateVisibility::Hidden);
}

void UTitleWidget::CallStartTyping()
{
	AMenuHUD* Hud = Cast<AMenuHUD>(mPlayerController->GetHUD());
	Hud->StartTyping(StoryDesc, 0.1f);
}




