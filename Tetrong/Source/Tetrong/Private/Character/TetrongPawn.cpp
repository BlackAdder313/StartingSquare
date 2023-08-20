#include "Character/TetrongPawn.h"

#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInput/Public/InputAction.h"
#include "Components/Input/TetrongEnhancedInputComponent.h"
#include "GameplayTags/TetrongGameplayTags.h"


//////////////////////////////////////////////////////////////////////////
// ATetrongPawn

ATetrongPawn::ATetrongPawn()
{
	// set our turn rates for input
	TurnRateGamepad = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	//FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

}

void ATetrongPawn::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}

//////////////////////////////////////////////////////////////////////////// Input

void ATetrongPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{

	UTetrongEnhancedInputComponent* enhancedInputComponent = Cast<UTetrongEnhancedInputComponent>(PlayerInputComponent);

	//Make sure to set your input component class in the InputSettings->DefaultClasses
	check(enhancedInputComponent);

	const FTetrongGameplayTags& GameplayTags = FTetrongGameplayTags::Get();

	//Bind Input actions by tag
	//enhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.GameInput_MoveBlock,	ETriggerEvent::Triggered,	 this, &ATetrongPawn::MoveBlock);
	enhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.GameInput_FallBlock,	ETriggerEvent::Triggered,	 this, &ATetrongPawn::FallBlock);
	enhancedInputComponent->BindActionByTag(InputConfig, GameplayTags.GameInput_RotateBoard,ETriggerEvent::Triggered,    this, &ATetrongPawn::RotateBoard);
}

void ATetrongPawn::OnPrimaryAction()
{
	// Trigger the OnItemUsed Event
	OnUseItem.Broadcast();
}

void ATetrongPawn::Input_Move(const FInputActionValue& InputActionValue)
{
	if (Controller != nullptr)
	{
		const FVector2D MoveValue = InputActionValue.Get<FVector2D>();
		const FRotator MovementRotation(0.0f, Controller->GetControlRotation().Yaw, 0.0f);

		if (MoveValue.X != 0.0f)
		{
			const FVector MovementDirection = MovementRotation.RotateVector(FVector::RightVector);
			AddMovementInput(MovementDirection, MoveValue.X);
		}

		if (MoveValue.Y != 0.0f)
		{
			const FVector MovementDirection = MovementRotation.RotateVector(FVector::ForwardVector);
			AddMovementInput(MovementDirection, MoveValue.Y);
		}
	}
}

void ATetrongPawn::MoveBlock(const FInputActionValue& InputActionValue)
{
	const FVector2D LookValue = InputActionValue.Get<FVector2D>();
	UE_LOG(LogBlueprintUserMessages, Log, TEXT("%f %f"), LookValue.X, LookValue.Y);
	
	//if (Controller != nullptr)
	//{
	//	//const FVector2D LookValue = InputActionValue.Get<FVector2D>();

	//	if (LookValue.X != 0.0f)
	//	{
	//		TurnAtRate(LookValue.X);
	//	}

	//	if (LookValue.Y != 0.0f)
	//	{
	//		LookUpAtRate(LookValue.Y);
	//	}
	//}
}

void ATetrongPawn::RotateBoard(const FInputActionValue& InputActionValue)
{
	//Jump();
}

void ATetrongPawn::FallBlock(const FInputActionValue& InputActionValue)
{
	OnPrimaryAction();
}

void ATetrongPawn::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void ATetrongPawn::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}