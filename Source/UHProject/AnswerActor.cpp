#include "AnswerActor.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

AAnswerActor::AAnswerActor()
{
    Button = CreateDefaultSubobject<UButton>(TEXT("Button"));
    Texts = CreateDefaultSubobject<UTextBlock>(TEXT("Texts"));

    FButtonStyle ButtonStyle = Button->GetStyle();
    FSlateBrush Brush;

    UTexture2D* RoundedTexture = LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/SeongWon/Art/circle-39475_640.circle-39475_640'"));
    Brush.SetResourceObject(RoundedTexture);
    Brush.TintColor = FSlateColor(FLinearColor(0, 0, 0, 0.2));
    Brush.DrawAs = ESlateBrushDrawType::Box;
    ButtonStyle.Normal = Brush;

    Brush.TintColor = FSlateColor(FLinearColor(0.2, 0.2, 0.2, 0.2));
    Brush.DrawAs = ESlateBrushDrawType::Box;
    ButtonStyle.Hovered = Brush;
    Button->SetStyle(ButtonStyle);

    FSlateFontInfo FontInfo = Texts->Font;
    FontInfo.FontObject = LoadObject<UObject>(nullptr, TEXT("/Script/Engine.Font'/Game/SeongWon/Font/GULIM_Font.GULIM_Font'"));
    Texts->SetFont(FontInfo);
}

void AAnswerActor::SetTextsAndNextRowName(const FText& NewAnswer, const FName& NextRowName)
{
    Texts->SetText(NewAnswer);
    Button->AddChild(Texts);
    Button->SetContent(Texts);
    AnswerNextRowName = NextRowName;
}

UButton* AAnswerActor::GetButton()
{
    return Button;
}

FName AAnswerActor::GetNextRowName()
{
    return AnswerNextRowName;
}
