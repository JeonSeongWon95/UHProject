#include "PressEWidget.h"
#include "Components/TextBlock.h"

void UPressEWidget::SetObjectName(FString NewName)
{
	ObjectName->SetText(FText::FromString(NewName));
}

void UPressEWidget::ShowPressEKeyText()
{
	PressEKey->SetVisibility(ESlateVisibility::Visible);
}

void UPressEWidget::HidePressEKeyText()
{
	PressEKey->SetVisibility(ESlateVisibility::Hidden);
}
