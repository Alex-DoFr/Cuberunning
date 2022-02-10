// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/CharacterEquipmentComponent.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Character.h"
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

	float ForwardAxis = 0.0f;
	float RightAxis = 0.0f;

protected:
	bool bIsWallRoning = false;
	EWallRunSide CurrentWalRunSide = EWallRunSide::None;
	FVector CurrentWallRunDirection = FVector::ZeroVector;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="WallRun")
	UCurveFloat* CameraTiltCurve;

	FTimeline CameraTilTimeline;

public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** Whether to use motion controller location for aiming. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	uint8 bUsingMotionControllers : 1;

protected:
	virtual void BeginPlay();
	
	void OnUseWeapon();
	
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

	UFUNCTION()
	void OnplayerCapsulHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	bool IsSurfaceWallRunnable(const FVector& SurfaceNormal) const;

	bool AreRequiredKeysDown(EWallRunSide Side) const;

	void StartWallRun(EWallRunSide Side, const FVector& Direction);
	void StopWallRun();
	void UpdatrWallRun();

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

