#include "DialogComponent.h"
#include "DialogueWidget.h"
#include "DialogStruct.h"
#include "NonPlayerCharacter.h"
#include "UHPlayerState.h"


UDialogComponent::UDialogComponent()
{
	static ConstructorHelpers::FClassFinder<UDialogueWidget> DW(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/SeongWon/BP/DialogSystem/BP_DialogWidget.BP_DialogWidget_C'"));

	if (DW.Succeeded()) 
	{
		mDialogueWidgetClass = DW.Class;
	}

	PrimaryComponentTick.bCanEverTick = true;

    CurrentDataTableRowName = "0";
}


void UDialogComponent::BeginPlay()
{
	Super::BeginPlay();

	if (mDialogueWidgetClass != nullptr) 
	{
		mDialogueWidget = Cast<UDialogueWidget>(CreateWidget<UDialogueWidget>(GetWorld(), mDialogueWidgetClass));
	}

	mDialogueWidget->SetDialogComponent(this);
	mNonPlayerCharacter = Cast<ANonPlayerCharacter>(GetOwner());
}


void UDialogComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UDialogComponent::SetSpeakName(const FText& Name)
{
	if (mDialogueWidget == nullptr) 
	{
		return;
	}

	mDialogueWidget->SetName(Name);
}

void UDialogComponent::StartTalk()
{
    mDialogueWidget->HideAnswerBox();
    

	if (CurrentDataTableRowName == "End") 
	{
		EndTalk();
		return;
	}
    else if (CurrentDataTableRowName == "A") 
    {
        ActionA();
    }
    else if (CurrentDataTableRowName == "B") 
    {
        ActionB();
    }
    else if (CurrentDataTableRowName == "C")
    {
        ActionC();
    }
    

	Dialog = mDialogDataTable->FindRow<FDialogStruct>(CurrentDataTableRowName, TEXT(""));

    if (Dialog == nullptr)
        return;

    if (!mDialogueWidget->IsInViewport())
    {
        mDialogueWidget->AddToViewport();
    }

    GetWorld()->GetTimerManager().SetTimer(TalkTimerHandle, this, &UDialogComponent::UpdateTalk, 0.05f, true);

    for (int i = 0; i < Dialog->Answers.Num(); ++i)
    {
        if (Dialog->Answers.Num() != Dialog->NextRows.Num())
            return;

        mDialogueWidget->AddAnswer(Dialog->Answers[i], Dialog->NextRows[i]);
    }
}

void UDialogComponent::SetNextRowName(const FName& NewName)
{
	CurrentDataTableRowName = NewName;

	if (NewName != "End")
	{
		LastDataTableRowName = CurrentDataTableRowName;
	}
}

void UDialogComponent::EndTalk()
{
	if (mDialogueWidget->IsInViewport()) 
	{
		mDialogueWidget->RemoveFromParent();
	}

	CurrentDataTableRowName = LastDataTableRowName;
	mNonPlayerCharacter->EndTalk();

}

void UDialogComponent::SetDialogDataTable(UDataTable* NewDataTable)
{
    mDialogDataTable = NewDataTable;
}

void UDialogComponent::SetStartDataTableRowName(FName StartName)
{
    CurrentDataTableRowName = StartName;
}

void UDialogComponent::UpdateTalk()
{
    if (Dialog->Dialog.Len() - 1 == DialogIndex) 
    {
        TransformDialog = "";
        DialogIndex = 0;
        GetWorld()->GetTimerManager().ClearTimer(TalkTimerHandle);
        mDialogueWidget->ShowAnswerBox();
    }
    else
    {
        TransformDialog.AppendChar(Dialog->Dialog[DialogIndex]);
        DialogIndex++;
        mDialogueWidget->SetDialog(FText::FromString(TransformDialog));
    }
}

void UDialogComponent::ActionB()
{
    mNonPlayerCharacter->DialogActionB();
}

void UDialogComponent::ActionC()
{
    mNonPlayerCharacter->DialogActionC();
}

void UDialogComponent::ActionA()
{
    mNonPlayerCharacter->DialogActionA();
}

