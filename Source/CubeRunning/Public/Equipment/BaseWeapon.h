// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

UCLASS()
class CUBERUNNING_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseWeapon();

	// Use Weapon
	virtual void Use();
	
	void SetCanUse(bool CanUse);

	FName GetAttachCktName() const {return AttachCktName;}

protected:
	UPROPERTY(VisibleDefaultsOnly, Category="WeaponMesh")
	class USkeletalMeshComponent* WeaponMesh;
	
	// After how many seconds can the weapon be reused
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="UsingWeapon")
	float DelayedReuse = 2.0f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="SocketName")
	FName AttachCktName;
	
	TWeakObjectPtr<class ACubeRunningCharacter> CachedCharacterOwner;
	
	// Is it possible to use weapons
	bool bCanUse = true;
	
	FTimerHandle DelayedReuseTimerHandle;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//virtual void OnRep_Owner() override;
	//
	bool CheckCanUse();

	// 
	void SetCanUseToTrue(){bCanUse = true;}
};
