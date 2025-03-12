#include "WorldLightManager.h"

AWorldLightManager::AWorldLightManager()
{
	PrimaryActorTick.bCanEverTick = true;

}


void AWorldLightManager::BeginPlay()
{
	Super::BeginPlay();
	
}


void AWorldLightManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWorldLightManager::LightOFF(int32 LightIndex)
{
    if (Lights.Num() < LightIndex)
        return;

    Lights[LightIndex]->GetRootComponent()->SetVisibility(false, true);

}

void AWorldLightManager::LightON(int32 LightIndex)
{
    if (Lights.Num() < LightIndex)
        return;

    Lights[LightIndex]->GetRootComponent()->SetVisibility(true, true);
}

