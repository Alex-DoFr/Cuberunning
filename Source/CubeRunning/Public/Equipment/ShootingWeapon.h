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
public:
	AShootingWeapon();

	void Use() override;
protected:
	UPROPERTY(VisibleDefaultsOnly,BlueprintReadOnly, Category="WeaponComponents")
	UBarrelComponent* Barrel;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="SocketName")
	FName MuzzelSktName;
};
