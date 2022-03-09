// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/CharacterEquipmentComponent.h"
#include "Components/CharacterHealthComponent.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Character.h"
#include "HUD/GameplayUW.h"
#include "CubeRunningCharacter.generated.h"

class USkeletalMeshComponent;
class UCameraComponent;

UENUM()
enum class EWallRunSide : uint8
{
	None,
	Left,
	Right
};

UCLASS(config=Game)
class ACubeRunningCharacter : public ACharacter
{
	GENERATED_BODY()

	
	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(VisibleAnywhere, Category = "EqipmantComponent")
	UCharacterEquipmentComponent* EquipmentComponent;
	
	UPROPERTY(VisibleAnywhere, Category = "HealthComponent")
	UCharacterHealthComponent* HealthComponent; 

	// Stores information about MoveForward Value
	float ForwardAxis = 0.0f;
	
	// Stores information about MoveRight Value
	float RightAxis = 0.0f;

protected:
	bool bIsWallRoning = false;
	
	// Stores information about which side of the wall the player is running on
	EWallRunSide CurrentWalRunSide = EWallRunSide::None;
	
	// Stores information about which direction the player is running in
	FVector CurrentWallRunDirection = FVector::ZeroVector;

	// The curve that determines at what speed and by what degree the camera deviates when running along the wall
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="WallRun")
	UCurveFloat* CameraTiltCurve;

	// Timeline of camera deflection when running on the wall
	FTimeline CameraTilTimeline;

public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Sprint")
	float MaxSprintSpeed = 1000.f;

	float WalkSpeed;

	bool IsSprinting = false;
	
	/** Whether to use motion controller location for aiming. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	uint8 bUsingMotionControllers : 1;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="UI")
	TSubclassOf<UGameplayUW> GameplayUWClass;

	UGameplayUW* GameplayUW;
protected:
	virtual void BeginPlay();
	
	void UseWeapon();
	
	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

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
	
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	
	void GetWallRunSideAndDirection(const FVector HitNormal, EWallRunSide& OutSide, FVector& OutDirection) const;

	//It is called when the capsule comes into contact with a surface and if this surface satisfies the conditions of running along the walls, the character starts running
	UFUNCTION()
	void OnplayerCapsulHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	bool IsSurfaceWallRunnable(const FVector& SurfaceNormal) const;

	//checks whether the character is moving forward and not trying to strafe in the opposite direction from the wall
	bool AreRequiredKeysDown(EWallRunSide Side) const;
	
	void StartWallRun(EWallRunSide Side, const FVector& Direction);
	
	void StopWallRun();

	// Checks every frame whether the character is running on the wall
	void UpdateWallRun();

	void StartSprinting();

	void StopSprinting();

	void UpdateSprinting();
	
	FORCEINLINE void BeginCameraTilt() {CameraTilTimeline.Play();}
	
	UFUNCTION()
	void UpdateCameraTilt(float Value);
	
	FORCEINLINE void EndCameraTilt() {CameraTilTimeline.Reverse();}
public:
	ACubeRunningCharacter();

	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	virtual void Jump() override;

	virtual void Tick(float DeltaSeconds) override;
};

