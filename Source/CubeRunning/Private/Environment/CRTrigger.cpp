// Fill out your copyright notice in the Description page of Project Settings.


#include "Environment/CRTrigger.h"
#include "Character/CubeRunningCharacter.h"
#include "Components/BoxComponent.h"

// Sets default values
ACRTriger::ACRTriger()
{
	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	TrigerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TrigerBox"));
	//TrigerBox->SetupAttachment(RootComponent);
}

void ACRTriger::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(ISActivate)
	{
		return;
	}
	
	if(OtherActor->IsA<ACubeRunningCharacter>())
	{
		//GEngine->AddOnScreenDebugMessage(-1,2.f,FColor::Blue,"ACRTriger::OnComponentBeginOverlap OtherComp is a ACubeRunningCharacter");
		ISActivate = true;
		ACharacter* PlayerCharacter = StaticCast<ACharacter*>(OtherActor);
		OnPlayerOverlap.Broadcast(PlayerCharacter);
		return;
	}
	//GEngine->AddOnScreenDebugMessage(-1,2.f,FColor::Red,"ACRTriger::OnComponentBeginOverlap OtherComp not is a ACubeRunningCharacter");
}

void ACRTriger::BeginPlay()
{
	Super::BeginPlay();

	TrigerBox->OnComponentBeginOverlap.AddDynamic(this, &ACRTriger::OnComponentBeginOverlap);
}



