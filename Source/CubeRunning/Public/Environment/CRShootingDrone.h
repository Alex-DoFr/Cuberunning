// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Environment/CRDrone.h"
#include "CRShootingDrone.generated.h"


UCLASS()
class CUBERUNNING_API ACRShootingDrone : public ACRDrone
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleDefaultsOnly,BlueprintReadOnly, Category="Components")
	class UBarrelComponent* BarrelComponent;

	UPROPERTY(VisibleDefaultsOnly,BlueprintReadOnly, Category="Components")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category="Fire")
	float FireDelay = 0.5f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category="Fire")
	float FireRate = 2.5f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="VisualEffects")
	USoundBase* FireSound;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="VisualEffects")
	UParticleSystem* FireParticle;
	
public:
	FTimerHandle FireTimerHandle;

	FTimerHandle FireDelayTimerHandle;
	
	ACRShootingDrone();

protected:
	UFUNCTION()
	void PreparationFire();

	UFUNCTION()
	void Fire();

	virtual void BeginPlay() override;

	virtual void Activate() override;

	virtual void TransitionToBatleState() override;
};
