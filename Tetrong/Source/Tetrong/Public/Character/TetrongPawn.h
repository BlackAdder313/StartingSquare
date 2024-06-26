#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TetrongPawn.generated.h"

class UTetrongEnhancedInputComponent;
class UInputConfig;
class USkeletalMeshComponent;
class UCameraComponent;
struct FInputActionValue;

// Declaration of the delegate that will be called when the Primary Action is triggered
// It is declared as dynamic so it can be accessed also in Blueprints
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUseItem);

UCLASS(config = Game)
class ATetrongPawn : public APawn
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

public:
	ATetrongPawn();

protected:
	virtual void BeginPlay();

public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float TurnRateGamepad;

	/** Delegate to whom anyone can subscribe to receive this event */
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnUseItem OnUseItem;

protected:

	/** Fires a projectile. */
	void OnPrimaryAction();

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }


	// Begin Enhanced Input Sample changes
public:

	/** The input config that maps Input Actions to Input Tags*/
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputConfig* InputConfig;

	UPROPERTY(BlueprintReadOnly)
	UTetrongEnhancedInputComponent* _enhancedComponent;

	/** Handles moving forward/backward */
	void Input_Move(const FInputActionValue& InputActionValue);

	/** Handles mouse and stick look */
	void MoveBlock(const FInputActionValue& InputActionValue);

	/** Handles Jumping */
	void RotateBoard(const FInputActionValue& InputActionValue);

	/** Handles Pew Pew */
	void FallBlock(const FInputActionValue& InputActionValue);

	// End Enhanced Input Sample changes
};