// Fill out your copyright notice in the Description page of Project Settings.


#include "Environment/CRShootingDrone.h"
#include "Equipment/Components/BarrelComponent.h"


ACRShootingDrone::ACRShootingDrone()
{
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMwsh"));
	WeaponMesh->SetupAttachment(DroneBody);
	BarrelComponent = CreateDefaultSubobject<UBarrelComponent>(TEXT("BarrelComponent"));
	BarrelComponent->SetupAttachment(WeaponMesh);
}

void ACRShootingDrone::PreparationFire()
{
	IsFollowPlayer = false;
	GetWorldTimerManager().SetTimer(FireDelayTimerHandle,this,&ACRShootingDrone::Fire, FireDelay);
}

void ACRShootingDrone::Fire()
{
	FVector Start = BarrelComponent->GetComponentLocation();
	FVector Direction = GetActorForwardVector();
	
	BarrelComponent->Shoot(Start,Direction, nullptr,this);
	IsFollowPlayer = true;
}

void ACRShootingDrone::BeginPlay()
{
	Super::BeginPlay();

	WeaponMesh->SetVisibility(false);

	BarrelComponent->SetFireSound(FireSound);
	BarrelComponent->SetFireParticle(FireParticle);
}

void ACRShootingDrone::Activate()
{
	Super::Activate();

	WeaponMesh->SetVisibility(true);
}

void ACRShootingDrone::TransitionToBatleState()
{
	Super::TransitionToBatleState();
	
	GetWorldTimerManager().SetTimer(FireTimerHandle,this,&ACRShootingDrone::PreparationFire, FireRate,true);
}
