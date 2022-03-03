// Fill out your copyright notice in the Description page of Project Settings.


#include "Environment/CRPlatform.h"


ACRplatform::ACRplatform()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	
	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform"));
	PlatformMesh->SetupAttachment(RootComponent);
}

void ACRplatform::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	switch (PlatformsTupe)
	{
	case EPlatformsTupe::flat:
		if(PlatformMeshFlat != nullptr)
		{
			PlatformMesh->SetStaticMesh(PlatformMeshFlat);
		}
		break;
		
	case EPlatformsTupe::cruciform:
		if(PlatformMeshFlat != nullptr)
		{
			PlatformMesh->SetStaticMesh(PlatformMeshCruciform);
		}
		break;
		
	default:
		if(PlatformMeshFlat != nullptr)
		{
			PlatformMesh->SetStaticMesh(PlatformMeshCruciform);
		}
	}
}


void ACRplatform::BeginPlay()
{
	Super::BeginPlay();
}


void ACRplatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

