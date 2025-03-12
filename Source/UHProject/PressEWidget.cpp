#include "PressEWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UPressEWidget::SetObjectName(FString NewName)
{
	ObjectName->SetText(FText::FromString(NewName));
}

void UPressEWidget::ShowPressEKeyText()
{
	EKeyImage->SetVisibility(ESlateVisibility::Visible);
}

void UPressEWidget::HidePressEKeyText()
{
    EKeyImage->SetVisibility(ESlateVisibility::Hidden);
}
