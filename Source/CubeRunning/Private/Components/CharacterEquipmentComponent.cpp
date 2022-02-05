// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CharacterEquipmentComponent.h"
#include "Character/CubeRunningCharacter.h"


// Sets default values for this component's properties
UCharacterEquipmentComponent::UCharacterEquipmentComponent()
{
	
}


// Called when the game starts
void UCharacterEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();
	
	checkf(GetOwner()->IsA<ACubeRunningCharacter>(), TEXT("UCharacterEquipmentComponent::BeginPlay() can de used only with CubeRunningCharacter"));
	CachedCharacterOwner = StaticCast<ACubeRunningCharacter*>(GetOwner());
	CreateLodout();
}

void UCharacterEquipmentComponent::CreateLodout()
{
	if(IsValid(LoadoutWeapon))
	{
		FActorSpawnParameters WeaponSpanwParameters = FActorSpawnParameters();;
		WeaponSpanwParameters.Owner = GetOwner();
		EquipWeapon = GetWorld()->SpawnActor<ABaseWeapon>(LoadoutWeapon,WeaponSpanwParameters);
		//EquipWeapon->SetOwner(GetOwner());
		EquipWeapon->AttachToComponent(CachedCharacterOwner->GetMesh1P(),FAttachmentTransformRules::SnapToTargetNotIncludingScale,EquipWeapon->GetAttachCktName());
	}
	else
	{
#if UE_BUILD_DEBUG || UE_BUILD_DEVELOPMENT
		if(GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red,"UCharacterEquipmentComponent::CreateLodout need set LoadoutWeapon");
		}
		UE_LOG(LogTemp, Warning, TEXT("UCharacterEquipmentComponent::CreateLodout need set LoadoutWeapon"));
#endif
	}
}




