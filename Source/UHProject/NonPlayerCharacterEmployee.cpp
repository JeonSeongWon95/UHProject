#include "NonPlayerCharacterEmployee.h"
#include "PickUpItemFood.h"

void ANonPlayerCharacterEmployee::DialogActionA()
{
    APickUpItemFood* CastFood = Cast<APickUpItemFood>(mFood);
    CastFood->SetUdon();

    GetWorld()->GetTimerManager().SetTimer(FoodTimerHandle, this, &ANonPlayerCharacterEmployee::ShowFood, 5.0f);
}

void ANonPlayerCharacterEmployee::DialogActionB()
{
    APickUpItemFood* CastFood = Cast<APickUpItemFood>(mFood);
    CastFood->SetRamen();

    GetWorld()->GetTimerManager().SetTimer(FoodTimerHandle, this, &ANonPlayerCharacterEmployee::ShowFood, 5.0f);
}

void ANonPlayerCharacterEmployee::DialogActionC()
{
}

void ANonPlayerCharacterEmployee::BeginPlay()
{
    Super::BeginPlay();

    if (mFood != nullptr)
    {
        HideFood();
    }
}

void ANonPlayerCharacterEmployee::ShowFood()
{
    if (mFood == nullptr)
        return;

    mFood->GetRootComponent()->SetVisibility(true, true);

    GetWorld()->GetTimerManager().ClearTimer(FoodTimerHandle);
}

void ANonPlayerCharacterEmployee::HideFood()
{
    if (mFood == nullptr)
        return;

    mFood->GetRootComponent()->SetVisibility(false, true);
}
