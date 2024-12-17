#include "UHProjectCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "UHPlayerState.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);


AUHProjectCharacter::AUHProjectCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
}

void AUHProjectCharacter::BeginPlay()
{
	Super::BeginPlay();

	mPlayerState = Cast<AUHPlayerState>(GetPlayerState());
}

void AUHProjectCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AUHProjectCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AUHProjectCharacter::Look);
	}
	else
	{

	}
}

void AUHProjectCharacter::LineTrace()
{
	FHitResult Result;

	FVector StartVector;
	FVector EndVector = StartVector * mLength;

	FCollisionObjectQueryParams Params;
	Params.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldDynamic);

	GetWorld()->LineTraceSingleByObjectType(Result, StartVector, EndVector, Params);
}


void AUHProjectCharacter::StartLineTrace()
{
	if (mPlayerState == nullptr || mPlayerState->IsLineTraceOn)
		return;

	mPlayerState->IsLineTraceOn = true;
	GetWorld()->GetTimerManager().SetTimer(LineTraceTimer, this, &AUHProjectCharacter::LineTrace, 0.1f, true);
}

void AUHProjectCharacter::StopLineTrace()
{
	if (mPlayerState == nullptr || !mPlayerState->IsLineTraceOn) 
		return;

	mPlayerState->IsLineTraceOn = false;
	GetWorld()->GetTimerManager().ClearTimer(LineTraceTimer);
}

void AUHProjectCharacter::Move(const FInputActionValue& Value)
{

	if (mPlayerState == nullptr || !mPlayerState->CanMove)
		return;

	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AUHProjectCharacter::Look(const FInputActionValue& Value)
{
	if (mPlayerState == nullptr || !mPlayerState->CanLook)
		return;

	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}