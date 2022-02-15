// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/BaseWeapon.h"
#include "Character/CubeRunningCharacter.h"



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

void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	AActor* OwningCharacter = GetOwner();
	if(OwningCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("Owner is Valid"));
		CachedCharacterOwner = StaticCast<ACubeRunningCharacter*>(OwningCharacter);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Owner is not Valid"));
	}
}

bool ABaseWeapon::CheckCanUse()
{
	if(bCanUse)
	{
		bCanUse = false;
		GetWorldTimerManager().SetTimer(DelayedReuseTimerHandle, this,&ABaseWeapon::SetCanUseToTrue, DelayedReuse);
		return true;
	}
	else
	{
		return false;
	}
}



