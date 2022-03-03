// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/BaseWeapon.h"
#include "Character/CubeRunningCharacter.h"



ABaseWeapon::ABaseWeapon()
{
 	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponRoot"));

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(RootComponent);
}

void ABaseWeapon::Use()
{
	if(!CheckCanUse())
	{
		return;
	}

	if(UseAnimMontage != nullptr)
	{
		CachedCharacterOwner->GetMesh1P()->GetAnimInstance()->Montage_Play(UseAnimMontage,1.f);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UseAnimMontage == nullptr"));
	}
}

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
		CachedCharacterOwner = StaticCast<ACubeRunningCharacter*>(OwningCharacter);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Owner is not Valid"));
	}
}

bool ABaseWeapon::CheckCanUse()
{
	return bCanUse;
}

void ABaseWeapon::SetUseDelay()
{
	bCanUse = false;
	GetWorldTimerManager().SetTimer(DelayedReuseTimerHandle, this,&ABaseWeapon::SetCanUseToTrue, DelayedReuse);
}



