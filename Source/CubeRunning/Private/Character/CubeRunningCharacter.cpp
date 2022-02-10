// Copyright Epic Games, Inc. All Rights Reserved.

#include "Character/CubeRunningCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// ACubeRunningCharacter

ACubeRunningCharacter::ACubeRunningCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
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
	
	EquipmentComponent = CreateDefaultSubobject<UCharacterEquipmentComponent>(TEXT("EquipmentComponent"));
}

void ACubeRunningCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	Mesh1P->SetHiddenInGame(false, true);

	GetCapsuleComponent()->OnComponentHit.AddDynamic(this,&ACubeRunningCharacter::OnplayerCapsulHit);

	GetCharacterMovement()->SetPlaneConstraintEnabled(true);

	if(IsValid(CameraTiltCurve))
	{
		FOnTimelineFloat TimelineCallBack;
		TimelineCallBack.BindUFunction(this,FName("UpdateCameraTilt"));
		CameraTilTimeline.AddInterpFloat(CameraTiltCurve, TimelineCallBack);
	}
}

	
//////////////////////////////////////////////////////////////////////////
// Input

void ACubeRunningCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ACubeRunningCharacter::OnUseWeapon);
	

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &ACubeRunningCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACubeRunningCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ACubeRunningCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ACubeRunningCharacter::LookUpAtRate);
}

void ACubeRunningCharacter::GetWallRunSideAndDirection(const FVector HitNormal, EWallRunSide& OutSide, FVector& OutDirection) const
{
	if(FVector::DotProduct(HitNormal,GetActorRightVector())>0)
	{
		OutSide = EWallRunSide::Left;
		OutDirection = FVector::CrossProduct(HitNormal,FVector::UpVector).GetSafeNormal();
	}
	else
	{
		OutSide = EWallRunSide::Right;
		OutDirection = FVector::CrossProduct(FVector::UpVector,HitNormal).GetSafeNormal();
	}
}

void ACubeRunningCharacter::OnplayerCapsulHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if(bIsWallRoning)
	{
		return;
	}
	
	FVector HitNormal = Hit.ImpactNormal;
	if(!IsSurfaceWallRunnable(HitNormal))
	{
		GEngine->AddOnScreenDebugMessage(-1,2,FColor::Red,"!IsSurfaceWallRunnable = true");
		return;
	}

	//if(GetCharacterMovement()->IsFalling())
	//{
	//	GEngine->AddOnScreenDebugMessage(-1,2,FColor::Red,"Character not falling");
	//	return;
	//}
	
	EWallRunSide Side = EWallRunSide::None;
	FVector Direction = FVector::ZeroVector;
	GetWallRunSideAndDirection(HitNormal, Side, Direction);

	if(!AreRequiredKeysDown(Side))
	{
		GEngine->AddOnScreenDebugMessage(-1,2,FColor::Red,"!AreRequiredKeysDown = true");
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1,2,FColor::Red,"We can runing on wall");
	StartWallRun(Side,Direction);
}

bool ACubeRunningCharacter::IsSurfaceWallRunnable(const FVector& SurfaceNormal) const
{
	return SurfaceNormal.Z < GetCharacterMovement()->GetWalkableFloorZ() && SurfaceNormal.Z>-0.005f;

	/*if(SurfaceNormal.Z > GetCharacterMovement()->GetWalkableFloorZ()|| SurfaceNormal.Z<-0.005f)
	{
		return false;
	}
	return true;*/
}

bool ACubeRunningCharacter::AreRequiredKeysDown(EWallRunSide Side) const
{
	if(ForwardAxis < 0.1f)
	{
		return false;
	}
	if(Side==EWallRunSide::Right && RightAxis <- 0.1f)
	{
		return false;
	}
	if(Side==EWallRunSide::Left && RightAxis > 0.1f)
	{
		return false;
	}
	return true;
}

void ACubeRunningCharacter::StartWallRun(EWallRunSide Side, const FVector& Direction)
{
	BeginCameraTilt();
	bIsWallRoning = true;
	
	CurrentWalRunSide = Side;
	CurrentWallRunDirection = Direction;
	
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector::UpVector);
}

void ACubeRunningCharacter::StopWallRun()
{
	EndCameraTilt();
	bIsWallRoning = false;
	//CurrentWalRunSide = EWallRunSide::None;
	//CurrentWallRunDirection = FVector::ZeroVector;
	
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector::ZeroVector);
}

void ACubeRunningCharacter::UpdatrWallRun()
{
	if(!AreRequiredKeysDown(CurrentWalRunSide))
	{
		StopWallRun();
		return;
	}
	
	FHitResult HitResult;
	
	FVector Start = GetActorLocation();
	FVector LTDirectional = CurrentWalRunSide==EWallRunSide::Right ? GetActorRightVector():-GetActorRightVector();
	float LTLenght = 200.0f;
	FVector End = Start+LTLenght*LTDirectional;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	
	if(GetWorld()->LineTraceSingleByChannel(HitResult,Start,End,ECC_Visibility,QueryParams))
	{
		EWallRunSide Side = EWallRunSide::None;
		FVector Direction = FVector::ZeroVector;
		GetWallRunSideAndDirection(HitResult.ImpactNormal, Side, Direction);

		if(Side!= CurrentWalRunSide)
		{
			StopWallRun();
		}
		else
		{
			CurrentWallRunDirection = Direction;
			GetCharacterMovement()->Velocity = GetCharacterMovement()->GetMaxSpeed()*CurrentWallRunDirection;
		}
	}
	else
	{
		StopWallRun();
	}
}

void ACubeRunningCharacter::UpdateCameraTilt(float Value)
{
	FRotator CurrentControlRotation = GetControlRotation();
	CurrentControlRotation.Roll = CurrentWalRunSide == EWallRunSide::Left? Value:-Value;
	GetController()->SetControlRotation(CurrentControlRotation);
}

void ACubeRunningCharacter::Jump()
{
	if(bIsWallRoning)
	{
		FVector JumpDirection = FVector::ZeroVector;
		if(CurrentWalRunSide==EWallRunSide::Right)
		{
			JumpDirection = FVector::CrossProduct(CurrentWallRunDirection,FVector::UpVector).GetSafeNormal();
		}
		else
		{
			JumpDirection = FVector::CrossProduct(FVector::UpVector,CurrentWallRunDirection).GetSafeNormal();
		}

		JumpDirection += FVector::UpVector;
		LaunchCharacter(GetCharacterMovement()->JumpZVelocity* JumpDirection.GetSafeNormal(),false,true);
		StopWallRun();
	}
	else
	{
		Super::Jump();
	}
}

void ACubeRunningCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if(bIsWallRoning)
	{
		UpdatrWallRun();
	}
	CameraTilTimeline.TickTimeline(DeltaSeconds);
}

void ACubeRunningCharacter::OnUseWeapon()
{
	if(EquipmentComponent)
	{
		EquipmentComponent->GetEquippedWeapon()->Use();
	}
}

void ACubeRunningCharacter::MoveForward(float Value)
{
	ForwardAxis = Value;
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ACubeRunningCharacter::MoveRight(float Value)
{
	RightAxis = Value;
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ACubeRunningCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ACubeRunningCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}




