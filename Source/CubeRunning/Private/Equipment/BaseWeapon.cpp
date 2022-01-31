// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/BaseWeapon.h"

// Sets default values
ABaseWeapon::ABaseWeapon()
{
 	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponRoot"));

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(RootComponent);

}

void ABaseWeapon::Use(){}

void ABaseWeapon::SetCanUse(bool CanUse)
{
	bCanUse = CanUse;
}

void ABaseWeapon::FlipFlopCanUse()
{
	bCanUse = !bCanUse;
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

bool ABaseWeapon::CheckCanUse()
{
	if(bCanUse)
	{
		FlipFlopCanUse();
		GetWorldTimerManager().SetTimer(DelayedReuseTimerHandle, this, &ABaseWeapon::FlipFlopCanUse, DelayedReuse);
		return  true;
	}
	else
	{
		return false;
	}
}



