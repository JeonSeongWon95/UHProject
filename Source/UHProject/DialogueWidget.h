#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogueWidget.generated.h"


UCLASS()
class UHPROJECT_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UTextBlock> SpeakerName;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UTextBlock> DialogBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UVerticalBox> AnswerBox;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<class UDialogComponent> mDialogComponent;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<class UBorder> DialogBoxBorder;

	UPROPERTY(BlueprintReadWrite)
	TArray<class AAnswerActor*> Answers;

	UPROPERTY(BlueprintReadWrite)
	int32 ButtonIndex = 0;
     
	UFUNCTION()
	void SetName(const FText& NewText);

	UFUNCTION()
	void AddAnswer(const FText& NewAnswer, const FName& NextRowName);

	UFUNCTION()
	void SetDialog(const FText& NewDialog);

	UFUNCTION()
	void OnClickedButtonZero();

	UFUNCTION()
	void OnClickedButtonOne();

	UFUNCTION()
	void OnClickedButtonTwo();

	UFUNCTION()
	void OnClickedButtonThree();

	UFUNCTION()
	void SetDialogComponent(UDialogComponent* NewDialogComponent);

	UFUNCTION()
	void RemoveAnswer();

    UFUNCTION()
    void ShowAnswerBox();

    UFUNCTION()
    void HideAnswerBox();

    virtual void NativeConstruct() override;
};
