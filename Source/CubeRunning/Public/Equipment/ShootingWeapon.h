// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BarrelComponent.h"
#include "Equipment/BaseWeapon.h"
#include "ShootingWeapon.generated.h"

/**
 * 
 */
UCLASS()
class CUBERUNNING_API AShootingWeapon : public ABaseWeapon
{
	GENERATED_BODY()

	
protected:
	// The barrel class responsible for the shot
	UPROPERTY(VisibleDefaultsOnly,BlueprintReadOnly, Category="WeaponComponents")
	UBarrelComponent* Barrel;

	// the name of the socket to attach to Barrel
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="SocketName")
	FName MuzzelSktName;

	virtual void BeginPlay() override;
	
public:
	AShootingWeapon();

	void Use() override;
};
