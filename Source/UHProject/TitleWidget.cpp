#include "TitleWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "MenuHUD.h"
#include "UHProjectPlayerController.h"

void UTitleWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ButtonGameStart)
	{
		ButtonGameStart->OnClicked.AddDynamic(this, &UTitleWidget::ClickedGameStart);
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
}

void UTitleWidget::ClickedGameStart()
{
	RemoveFromParent();
	mPlayerController->FadeOut();
	mPlayerController->HideMouseCursor();
	GetWorld()->GetTimerManager().SetTimer(mStartTypingTimerHandle, this, &UTitleWidget::CallStartTyping, 5.0f, false);
}

void UTitleWidget::ClickedOption()
{

}

void UTitleWidget::ClickedQuit()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}

void UTitleWidget::CallStartTyping()
{
	AMenuHUD* Hud = Cast<AMenuHUD>(mPlayerController->GetHUD());
	Hud->StartTyping("This is my story from a long time ago.", 0.2f);

	//이것은 오래전 나의 이야기다.\n지역 출장 때문에 5일 동안 먼 곳으로 운전을 하며 다녔다.\n근처에 숙소도 없어서 어쩔 수 없이 출퇴근을 반복해야 했다.\n정해진 시간에 잠을 자는 규칙적인 생활을 하던 나에게 새벽 운전은 무척 고된 일이었다.\n장시간 운전으로 지친 나는 종종 휴게소에 들러 식사를 하거나 잠시 눈을 붙이곤 했다.
}




