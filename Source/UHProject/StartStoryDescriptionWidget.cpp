#include "StartStoryDescriptionWidget.h"
#include "Components/TextBlock.h"

void UStartStoryDescriptionWidget::SetText(FText NewText)
{
	DescriptionText->SetText(NewText);
}
