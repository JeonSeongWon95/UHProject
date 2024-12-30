#include "DialogueWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "AnswerStruct.h"
#include "DialogComponent.h"

void UDialogueWidget::SetName(const FText& NewText)
{
	SpeakerName->SetText(NewText);
}

void UDialogueWidget::AddAnswer(const FText& NewAnswer,const FName& NextRowName)
{
	FAnswerStruct* NewAnswerStruct = new FAnswerStruct();
	NewAnswerStruct->Button = NewObject<UButton>(this);
	NewAnswerStruct->Texts = NewObject<UTextBlock>(this);

	NewAnswerStruct->Texts->SetText(NewAnswer);
	NewAnswerStruct->Button->AddChild(NewAnswerStruct->Texts);
	NewAnswerStruct->AnswerNextRowName = NextRowName;
	AnswerBox->AddChildToVerticalBox(NewAnswerStruct->Button);

	switch (ButtonIndex)
	{
	case 0:
		NewAnswerStruct->Button->OnClicked.AddDynamic(this, &UDialogueWidget::OnClickedButtonZero);
		break;
	case 1:
		NewAnswerStruct->Button->OnClicked.AddDynamic(this, &UDialogueWidget::OnClickedButtonOne);
		break;
	case 2:
		NewAnswerStruct->Button->OnClicked.AddDynamic(this, &UDialogueWidget::OnClickedButtonTwo);
		break;
	case 3:
		NewAnswerStruct->Button->OnClicked.AddDynamic(this, &UDialogueWidget::OnClickedButtonThree);
		break;
	default:
		break;
	}

	Answers.Add(*NewAnswerStruct);
	ButtonIndex++;

}

void UDialogueWidget::SetDialog(const FText& NewDialog)
{
	DialogBox->SetText(NewDialog);
}

void UDialogueWidget::OnClickedButtonZero()
{
	
	mDialogComponent->SetNextRowName(Answers[0].AnswerNextRowName);
	RemoveAnswer();
	mDialogComponent->StartTalk();
}

void UDialogueWidget::OnClickedButtonOne()
{
	mDialogComponent->SetNextRowName(Answers[1].AnswerNextRowName);
	RemoveAnswer();
	mDialogComponent->StartTalk();
}

void UDialogueWidget::OnClickedButtonTwo()
{
	mDialogComponent->SetNextRowName(Answers[2].AnswerNextRowName);
	RemoveAnswer();
	mDialogComponent->StartTalk();
}

void UDialogueWidget::OnClickedButtonThree()
{
	mDialogComponent->SetNextRowName(Answers[3].AnswerNextRowName);
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
