// Fill out your copyright notice in the Description page of Project Settings.


#include "Environment/CRThornsPlatform.h"

void ACRThornsPlatform::BeginPlay()
{
	Super::BeginPlay();

	PainBox->OnComponentBeginOverlap.AddDynamic(this,&ACRThornsPlatform::OnComponentBeginOverlap);
}

void ACRThornsPlatform::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OtherActor->TakeDamage(2,FDamageEvent(),nullptr,this);
	//GEngine->AddOnScreenDebugMessage(-1,2,FColor::Green,"ACRThornsPlatform::OnComponentBeginOverlap");
}

ACRThornsPlatform::ACRThornsPlatform()
{
	ThornsMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Thorns"));
	ThornsMesh->SetupAttachment(PlatformMesh);

	PainBox = CreateDefaultSubobject<UBoxComponent>(TEXT("PainBox"));
	PainBox->SetupAttachment(PlatformMesh);
}
