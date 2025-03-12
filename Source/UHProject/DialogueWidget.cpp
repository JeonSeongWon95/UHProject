#include "DialogueWidget.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "AnswerActor.h"
#include "DialogComponent.h"
#include "Components/Spacer.h"
#include "Components/Border.h"
#include "Components/SizeBox.h"

void UDialogueWidget::SetName(const FText& NewText)
{
	SpeakerName->SetText(NewText);
}

void UDialogueWidget::AddAnswer(const FText& NewAnswer,const FName& NextRowName)
{
    AAnswerActor* mAnswer = NewObject<AAnswerActor>(this);
    USpacer* Spacer = NewObject<USpacer>(this);
    mAnswer->SetTextsAndNextRowName(NewAnswer, NextRowName);
	AnswerBox->AddChildToVerticalBox(Cast<UWidget>(mAnswer->GetButton()));
    Spacer->SetSize(FVector2D(0, 30));
    AnswerBox->AddChildToVerticalBox(Spacer);

	switch (ButtonIndex)
	{
	case 0:
        mAnswer->GetButton()->OnClicked.AddDynamic(this, &UDialogueWidget::OnClickedButtonZero);
		break;
	case 1:
        mAnswer->GetButton()->OnClicked.AddDynamic(this, &UDialogueWidget::OnClickedButtonOne);
		break;
	case 2:
        mAnswer->GetButton()->OnClicked.AddDynamic(this, &UDialogueWidget::OnClickedButtonTwo);
		break;
	case 3:
        mAnswer->GetButton()->OnClicked.AddDynamic(this, &UDialogueWidget::OnClickedButtonThree);
		break;
	default:
		break;
	}

	Answers.Add(mAnswer);
	ButtonIndex++;

}

void UDialogueWidget::SetDialog(const FText& NewDialog)
{
	DialogBox->SetText(NewDialog);
}

void UDialogueWidget::OnClickedButtonZero()
{
	
	mDialogComponent->SetNextRowName(Answers[0]->GetNextRowName());
	RemoveAnswer();
	mDialogComponent->StartTalk();
}

void UDialogueWidget::OnClickedButtonOne()
{
	mDialogComponent->SetNextRowName(Answers[1]->GetNextRowName());
	RemoveAnswer();
	mDialogComponent->StartTalk();
}

void UDialogueWidget::OnClickedButtonTwo()
{
	mDialogComponent->SetNextRowName(Answers[2]->GetNextRowName());
	RemoveAnswer();
	mDialogComponent->StartTalk();
}

void UDialogueWidget::OnClickedButtonThree()
{
	mDialogComponent->SetNextRowName(Answers[3]->GetNextRowName());
	RemoveAnswer();
	mDialogComponent->StartTalk();
}

void UDialogueWidget::SetDialogComponent(UDialogComponent* NewDialogComponent)
{
	mDialogComponent = NewDialogComponent;
}

void UDialogueWidget::RemoveAnswer()
{
	ButtonIndex = 0;
	AnswerBox->ClearChildren();
	Answers.Empty();
}

void UDialogueWidget::ShowAnswerBox()
{
    AnswerBox->SetVisibility(ESlateVisibility::Visible);
}

void UDialogueWidget::HideAnswerBox()
{
    AnswerBox->SetVisibility(ESlateVisibility::Hidden);
}

void UDialogueWidget::NativeConstruct()
{
    Super::NativeConstruct();

    DialogBoxBorder = NewObject<UBorder>(this);

    FSlateBrush Brush;
    UTexture2D* RoundedTexture = LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/SeongWon/Art/circle-39475_640.circle-39475_640'"));
    Brush.SetResourceObject(RoundedTexture);
    Brush.TintColor = FSlateColor(FLinearColor(0, 0, 0, 0.2));
    Brush.DrawAs = ESlateBrushDrawType::Box;

    DialogBoxBorder->SetBrush(Brush);
}
