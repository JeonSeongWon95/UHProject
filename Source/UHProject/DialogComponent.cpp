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

	static ConstructorHelpers::FObjectFinder<UDataTable> DialogDataTable(TEXT("/Script/Engine.DataTable'/Game/SeongWon/BP/DialogSystem/DialogDataTable.DialogDataTable'"));

	if (DialogDataTable.Succeeded())
	{
		mDialogDataTable = DialogDataTable.Object;
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
	if (CurrentDataTableRowName == "End") 
	{
		EndTalk();
		return;
	}

	FDialogStruct* Dialog = mDialogDataTable->FindRow<FDialogStruct>(CurrentDataTableRowName, TEXT(""));

	if (Dialog != nullptr)
	{

		for (int i = 0; i < Dialog->AnswersCount; ++i) 
		{
			mDialogueWidget->AddAnswer(Dialog->Answers[i], Dialog->NextRows[i]);
		}

		mDialogueWidget->SetDialog(Dialog->Dialog);

		if (!mDialogueWidget->IsInViewport())
		{
			mDialogueWidget->AddToViewport();
		}
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

