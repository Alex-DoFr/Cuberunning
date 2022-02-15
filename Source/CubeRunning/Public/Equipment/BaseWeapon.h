// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

UCLASS()
class CUBERUNNING_API ABaseWeapon : public AActor
{
	GENERATED_BODY()


protected:
	// Skeletal mesh of weapons
	UPROPERTY(VisibleDefaultsOnly, Category="WeaponMesh")
	class USkeletalMeshComponent* WeaponMesh;
	
	// After how many seconds can the weapon be reused
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="UsingWeapon")
	float DelayedReuse = 2.0f;

	// The name of the socket to which this weapon should be attached
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="SocketName")
	FName AttachCktName;

	// Weak reference to the gun owner
	TWeakObjectPtr<class ACubeRunningCharacter> CachedCharacterOwner;
	
	// Is it possible to use weapons
	bool bCanUse = true;

	// Timer handle responsible for delayed reuse
	FTimerHandle DelayedReuseTimerHandle;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// If this weapon can be used return true and starts a timer to delay the use of the weapon
	bool CheckCanUse();
	
	// A function for the DelayedReuseTimerHandle.
	UFUNCTION()
	void SetCanUseToTrue(){bCanUse = true;}
	
public:	
	ABaseWeapon();

	// Virtual function for overloading in descendant classes
	virtual void Use();

	// Set a variable responsible for whether a weapon can fire
	void SetCanUse(bool CanUse);

	// Returns the name of the socket to which this weapon should be attached
	FName GetAttachCktName() const {return AttachCktName;}
};
