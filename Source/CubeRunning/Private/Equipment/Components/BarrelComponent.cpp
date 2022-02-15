// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/Components/BarrelComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UBarrelComponent::UBarrelComponent()
{
	
}

void UBarrelComponent::Shoot(FVector Start, FVector Direction, AController* Controller)
{
	FVector ShootEnd = Start+Direction*FireRange;
	FHitResult ShootResult;
	if(GetWorld()->LineTraceSingleByChannel(ShootResult,Start,ShootEnd, ECC_Visibility))
	{
		GEngine->AddOnScreenDebugMessage(-1,2.0f,FColor::Green,"Shot");
		ShootEnd = ShootResult.ImpactPoint;
		AActor* HitActor = ShootResult.GetActor();
		if(IsValid(HitActor))
		{
			HitActor->TakeDamage(DamageAmount,FDamageEvent{},Controller ,GetOwner());
			GEngine->AddOnScreenDebugMessage(-1,2.0f,FColor::Green,HitActor->GetName());
		}
#if UE_BUILD_DEBUG || UE_BUILD_DEVELOPMENT
		DrawDebugSphere(GetWorld(),ShootEnd,10.0f,24,FColor::Red,false,20.0f);
		DrawDebugLine(GetWorld(),Start,ShootEnd,FColor::Green,false,20.0f,0,3.0f);
#endif
	}
}







