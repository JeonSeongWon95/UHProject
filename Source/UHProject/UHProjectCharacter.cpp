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
#include "ObjectInterface.h"
#include "MenuHUD.h"
#include "Item.h"
#include "PickUpItem.h"
#include "ItemSlot.h"
#include "UHProjectPlayerController.h"
#include "UHProjectGameMode.h"
#include "UHProjectPlayerCar.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SpotLightComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "WorldBackGroundMusicManager.h"
#include "SoliloquyStruct.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

AUHProjectCharacter::AUHProjectCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

    mCameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    mCameraBoom->SetupAttachment(GetCapsuleComponent());
    mCameraBoom->TargetArmLength = 0.0f;
    mCameraBoom->bUsePawnControlRotation = true;

    FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
    FirstPersonCameraComponent->SetupAttachment(mCameraBoom);
    FirstPersonCameraComponent->bUsePawnControlRotation = false;

    mFlashLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("FlashLight"));
    mFlashLight->SetupAttachment(FirstPersonCameraComponent);

    mFlashLightInner = CreateDefaultSubobject<USpotLightComponent>(TEXT("FlashLightInner"));
    mFlashLightInner->SetupAttachment(mFlashLight);

	mItemSlot = CreateDefaultSubobject<UItemSlot>(TEXT("ItemSlot"));
	mItemSlot->SetupAttachment(GetCapsuleComponent());

	mLength = 150.0f;

    CurrentDataTableIndex = 0;
    CurrentDataTableRowName = FName(*FString::FromInt(CurrentDataTableIndex));

}

void AUHProjectCharacter::BeginPlay()
{
    Super::BeginPlay();

    mPlayerState = Cast<AUHPlayerState>(GetPlayerState());
    mPlayerController = Cast<AUHProjectPlayerController>(mPlayerState->GetPlayerController());
    mHUD = Cast<AMenuHUD>(mPlayerController->GetHUD());
    AUHProjectGameMode* GameMode = Cast<AUHProjectGameMode>(GetWorld()->GetAuthGameMode());

    GameMode->mPlayerCharacter = this;
    GameMode->mPlayerState = mPlayerState;
    GameMode->mPlayerController = mPlayerController;
    GameMode->mPlayerCar = mPlayerCar;

    mFlashLight->SetVisibility(false, true);

}

void AUHProjectCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AUHProjectCharacter::Move);
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &AUHProjectCharacter::StopMove);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AUHProjectCharacter::Look);
		EnhancedInputComponent->BindAction(InteractionAction, ETriggerEvent::Started, this, &AUHProjectCharacter::Interaction);
        EnhancedInputComponent->BindAction(ToggleAction, ETriggerEvent::Started, this, &AUHProjectCharacter::ToggleFlashLight);
        EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &AUHProjectCharacter::Sprint);
        EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AUHProjectCharacter::StopSprint);
	}
}

void AUHProjectCharacter::LineTrace()
{
	FHitResult Result;

	FVector CameraLocation;
	FRotator CameraRotation;

	GetController()->GetPlayerViewPoint(CameraLocation, CameraRotation);

	FVector StartVector = CameraLocation;
	FVector EndVector = StartVector + (CameraRotation.Vector() * mLength);

	FCollisionObjectQueryParams Params;
	FCollisionQueryParams CollisionParams;
	Params.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldDynamic);
	CollisionParams.AddIgnoredActor(this);
    
	
	bool HitResult = GetWorld()->LineTraceSingleByObjectType(Result, StartVector, EndVector, Params, CollisionParams);

	FColor LineColor = HitResult ? FColor::Green : FColor::Red;
	DrawDebugLine(GetWorld(), StartVector, EndVector, LineColor, false, 1.0f, 0, 2.0f);

	if (!HitResult)
	{
		mHUD->RemoveObjectPopUp();
		return;
	}

	mCurrentHitItem = Cast<AItem>(Result.GetActor());

	if (mCurrentHitItem != nullptr)
	{
		mHUD->SetAndShowObjectPopUp(mCurrentHitItem->Name, true);
	}
	else
	{
		mHUD->SetAndShowObjectPopUp(mCurrentHitItem->Name, false);
	}
}

void AUHProjectCharacter::StartLineTrace()
{
	if (mPlayerState == nullptr || mPlayerState->IsLineTraceOn)
		return;

	mPlayerState->IsLineTraceOn = true;
    UE_LOG(LogTemp, Warning, TEXT("Start LineTrace"))
	GetWorld()->GetTimerManager().SetTimer(LineTraceTimer, this, &AUHProjectCharacter::LineTrace, 0.1f, true);
}

void AUHProjectCharacter::StopLineTrace()
{
	if (mPlayerState == nullptr || !mPlayerState->IsLineTraceOn) 
		return;

	mHUD->RemoveObjectPopUp();
	mPlayerState->IsLineTraceOn = false;
	mCurrentHitItem = nullptr;
	GetWorld()->GetTimerManager().ClearTimer(LineTraceTimer);
}

void AUHProjectCharacter::EquipItem(APickUpItem* SelectedItem)
{
	if (mPlayerState->IsEquip) 
	{
		UnEquipItem();
	}

	mEquipItem = SelectedItem;
	mEquipItem->DisableLineTraceCollisionAndPhyiscs();
	mEquipItem->AttachToComponent(mItemSlot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	mPlayerState->IsEquip = true;
}

void AUHProjectCharacter::UnEquipItem()
{
	mEquipItem->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	mEquipItem->EnableLineTraceCollisionAndPhyiscs();
	mEquipItem = nullptr;
	mPlayerState->IsEquip = false;
}

void AUHProjectCharacter::GetOutTheCar()
{
    if (mPlayerCar != nullptr)
    {

        if (mWorldBGMManager != nullptr)
        {
            if (mWorldBGMManager->GetCurrentBGMType() != EBGMType::Rain_In_The_OutSide)
            {
                mWorldBGMManager->SetMusic(EBGMType::Rain_In_The_OutSide);
            }

            mWorldBGMManager->PlayMusic();
        }

        mPlayerCar->PlaySoundBase();
        mPlayerState->CanMove = true;
        mPlayerState->CanLook = true;
        mPlayerState->IsInTheCar = false;

        GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
        DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

        FVector SetLocation = mPlayerCar->GetDriverLocation();
        SetLocation.X += 200.0f;

        GetCharacterMovement()->GravityScale = 1.0f;
        SetActorLocation(SetLocation);
        mPlayerCar->SetMeshCollision(true);
    }
}

void AUHProjectCharacter::TurnOnOrOFFFlashLight(bool IsTurnOn)
{
    mPlayerState->TurnOnFlashLight = IsTurnOn;
    UGameplayStatics::PlaySoundAtLocation(GetWorld(), FlashLightToggleSound, GetActorLocation());

    if (IsTurnOn) 
    {
        mFlashLight->SetVisibility(true, true);

    }
    else 
    {
        mFlashLight->SetVisibility(false, true);
    }
}

void AUHProjectCharacter::PlayerDriveStart()
{
    mPlayerCar->Drive();
}

void AUHProjectCharacter::ResetCharacter()
{
    StartLineTrace();
    mPlayerState->CanLook = true;
}

void AUHProjectCharacter::Soliloquy()
{
    SoliloquyStruct = mSoliloquyDataTable->FindRow<FSoliloquyStruct>(CurrentDataTableRowName, TEXT(""));

    if (SoliloquyStruct == nullptr)
        return;

    mHUD->StartSoliloquy(FText::FromString(SoliloquyStruct->Soliloquy));

    if (CurrentDataTableIndex < mSoliloquyDataTable->GetRowNames().Num())
    {
        CurrentDataTableIndex++;
    }
    CurrentDataTableRowName = FName(*FString::FromInt(CurrentDataTableIndex));

}

void AUHProjectCharacter::TraceFootStep()
{
    FVector SphereTraceEndpoint = GetActorLocation();
    SphereTraceEndpoint.Z -= GetCapsuleComponent()->GetScaledCapsuleHalfHeight();

    TArray<AActor*> IgnoreActor;
    FHitResult Result;

    if (UKismetSystemLibrary::SphereTraceSingle(GetWorld(), GetActorLocation(), SphereTraceEndpoint,
        GetCapsuleComponent()->GetScaledCapsuleRadius(), UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_Visibility),
        false, IgnoreActor, EDrawDebugTrace::None, Result, true)) 
    {

        UPhysicalMaterial* PhysMaterial = Result.PhysMaterial.Get();
        
        
        if (PhysMaterial == nullptr)
            return;

        EPhysicalSurface SurfaceType = PhysMaterial->SurfaceType;

        switch (SurfaceType)
        {
        case SurfaceType_Default:
            UGameplayStatics::PlaySoundAtLocation(GetWorld(), FootStepSound_OutSide, GetActorLocation());
            break;

        case SurfaceType1:
            UGameplayStatics::PlaySoundAtLocation(GetWorld(), FootStepSound_InSide, GetActorLocation());
            break;

        case SurfaceType2:
            break;
        case SurfaceType3:
            break;
        case SurfaceType4:
            break;
        case SurfaceType5:
            break;
        case SurfaceType6:
            break;
        case SurfaceType7:
            break;
        case SurfaceType8:
            break;
        case SurfaceType9:
            break;
        case SurfaceType10:
            break;
        default:
            break;
        }
    }
}

void AUHProjectCharacter::GetInTheCar()
{

    if(mPlayerCar != nullptr)
    {
        mPlayerCar->PlaySoundBase();

        if (mWorldBGMManager != nullptr) 
        {
            if (mWorldBGMManager->GetCurrentBGMType() != EBGMType::Rain_In_The_Car)
            {
                mWorldBGMManager->SetMusic(EBGMType::Rain_In_The_Car);
            }

            mWorldBGMManager->PlayMusic();
        }

        mPlayerCar->SetMeshCollision(false);
        mPlayerState->CanMove = false;
        mPlayerState->CanLook = true;
        mPlayerState->IsInTheCar = true;
        GetCharacterMovement()->GravityScale = 0.0f;
        GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

        StartLineTrace();
        SetActorLocation(mPlayerCar->GetDriverLocation());

        AttachToActor(mPlayerCar, FAttachmentTransformRules::KeepWorldTransform);
    }
}

void AUHProjectCharacter::Move(const FInputActionValue& Value)
{

	if (mPlayerState == nullptr)
		return;

    if (!mPlayerState->CanMove)
    {
        return;
    }

    FVector2D MovementVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        AddMovementInput(GetActorForwardVector(), MovementVector.Y);
        AddMovementInput(GetActorRightVector(), MovementVector.X);

        if (MovementVector.Length() != 0)
        {
            FootStepTimer += GetWorld()->GetDeltaSeconds();
            float Delay = mPlayerState->IsSprint == true ? 0.5f : 1.0f;

            if (FootStepTimer >= Delay)
            {
                FootStepTimer = 0;
                TraceFootStep();
            }
        }
    }
}

void AUHProjectCharacter::StopMove(const FInputActionValue& Value)
{
    FootStepTimer = 0;
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

void AUHProjectCharacter::Interaction(const FInputActionValue& Value)
{
	if (mCurrentHitItem == nullptr || !mPlayerState->IsLineTraceOn)
	{
		UE_LOG(LogTemp, Error, TEXT("Current Hit Actor is Nullptr"))
		return;
	}

	if (mCurrentHitItem->Implements<UObjectInterface>())
	{
		IObjectInterface* ObjectInterface = Cast<IObjectInterface>(mCurrentHitItem);

		if (ObjectInterface)
		{
			IObjectInterface::Execute_Interaction(mCurrentHitItem);
			mCurrentHitItem = nullptr;
			mHUD->RemoveObjectPopUp();
		}
	}
	else 
	{

	}
}

void AUHProjectCharacter::ToggleFlashLight(const FInputActionValue& Value)
{
    if (!mPlayerState->HasFlashLight)
        return;

    if (mPlayerState->TurnOnFlashLight) 
    {       
        TurnOnOrOFFFlashLight(false);
    }
    else 
    {
        TurnOnOrOFFFlashLight(true);
    }
}

void AUHProjectCharacter::Sprint(const FInputActionValue& Value)
{
    mPlayerState->IsSprint = true;
    GetCharacterMovement()->MaxWalkSpeed = 600.0f;    
}

void AUHProjectCharacter::StopSprint(const FInputActionValue& Value)
{
    mPlayerState->IsSprint = false;
    GetCharacterMovement()->MaxWalkSpeed = 300.0f;
}
