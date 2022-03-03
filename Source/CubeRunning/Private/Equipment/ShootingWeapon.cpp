// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/ShootingWeapon.h"
#include "Character/CubeRunningCharacter.h"

void AShootingWeapon::BeginPlay()
{
	Super::BeginPlay();

	Barrel->SetFireSound(FireSound);
	Barrel->SetFireParticle(FireParticle);
}

AShootingWeapon::AShootingWeapon()
{
	Barrel = CreateDefaultSubobject<UBarrelComponent>(TEXT("BarrelCpmponent"));
	Barrel->SetupAttachment(WeaponMesh,MuzzelSktName);
}

void AShootingWeapon::Use()
{
	Super::Use();

	if(!CachedCharacterOwner.IsValid())
	{
		return;
	}
	
	if(!CheckCanUse())
	{
		return;
	}

	SetUseDelay();
	AController* Controller = CachedCharacterOwner->GetController();
	FVector ShootStatr;
	FRotator ShootRotation;
	FVector ShootDirecrion;

	Controller->GetPlayerViewPoint(ShootStatr,ShootRotation);

	ShootDirecrion = ShootRotation.RotateVector(FVector::ForwardVector);
	
	Barrel->Shoot(ShootStatr,ShootDirecrion,Controller);
}
