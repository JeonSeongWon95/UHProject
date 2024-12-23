#include "CurrentDayPrintWidget.h"
#include "Components/TextBlock.h"

void UCurrentDayPrintWidget::SetText(FText NewText)
{
	CurrentDay->SetText(NewText);
}
