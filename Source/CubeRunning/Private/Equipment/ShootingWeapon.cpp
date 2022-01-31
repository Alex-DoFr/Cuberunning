// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/ShootingWeapon.h"

AShootingWeapon::AShootingWeapon()
{
	Barrel = CreateDefaultSubobject<UBarrelComponent>(TEXT("BarrelCpmponent"));
	Barrel->SetupAttachment(WeaponMesh,MuzzelSktName);
}

void AShootingWeapon::Use()
{
	Super::Use();

	if(CheckCanUse())
	{
		//Barrel->Shoot();
	}
	
}
