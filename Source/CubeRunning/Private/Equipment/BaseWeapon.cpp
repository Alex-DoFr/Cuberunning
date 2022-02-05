// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/BaseWeapon.h"
#include "Character/CubeRunningCharacter.h"


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

// Called when the game starts or when spawned
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

/*void ABaseWeapon::OnRep_Owner()
{
	Super::OnRep_Owner();

	UE_LOG(LogTemp, Warning, TEXT("Called OnRep_Owner"));
	if(GetOwner()->IsA<ACubeRunningCharacter>())
	{
		CachedCharacterOwner = StaticCast<ACubeRunningCharacter*>(GetOwner());
		UE_LOG(LogTemp, Warning, TEXT("BeginPlay set owner"));
	}
}*/

bool ABaseWeapon::CheckCanUse()
{
	if(bCanUse)
	{
		bCanUse = false;
		GetWorldTimerManager().SetTimer(DelayedReuseTimerHandle, this,&ABaseWeapon::SetCanUseToTrue, DelayedReuse);
		return  true;
	}
	else
	{
		return false;
	}
}



