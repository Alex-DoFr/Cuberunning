// Fill out your copyright notice in the Description page of Project Settings.


#include "Environment/CRDrone.h"

#include "Core/CubeRunningGameMode.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


ACRDrone::ACRDrone()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	DroneBody = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("DroneBody"));
	DroneBody->SetupAttachment(RootComponent);
}

void ACRDrone::BeginPlay()
{
	Super::BeginPlay();

	if(IsValid(Triger))
	{
		Triger->OnPlayerOverlap.AddUFunction(this,FName("OnCalled"));
	}

	DroneBody->SetVisibility(false);
	
	if(IsValid(DroneTakeoffCurve))
	{
		FOnTimelineFloat TimelineCallBack;
		TimelineCallBack.BindUFunction(this,FName("MoveDrone"));
		DroneTakeoffTimeline.AddInterpFloat(DroneTakeoffCurve, TimelineCallBack);
		
		FOnTimelineEvent TimelineFinishedFunc;
		TimelineFinishedFunc.BindUFunction(this,FName("TransitionToBatleState"));
		DroneTakeoffTimeline.SetTimelineFinishedFunc(TimelineFinishedFunc);
	}

	OnTakeAnyDamage.AddDynamic(this,&ACRDrone::OnTakeDamage);
}

void ACRDrone::Activate()
{
	if (ActivateSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ActivateSound, GetActorLocation());
	}
	
	IsFollowPlayer = true;
	IsActivate = true;
	DroneBody->SetVisibility(true);

	StartLocation = GetActorLocation();
	EndLocation+=StartLocation;
	DroneTakeoffTimeline.Play();
}

void ACRDrone::TransitionToBatleState()
{}

void ACRDrone::MoveDrone(float Value)
{
	FVector Location = FMath::Lerp(StartLocation,EndLocation,Value);
	SetActorLocation(Location);
}

void ACRDrone::OnCalled(ACharacter* PlayerCharacter)
{
	if(!PlayerCharacter)
	{
		return;
	}
	
	CashedPlayerCharacter=PlayerCharacter;
	Activate();
}

void ACRDrone::OnTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if(DestroySound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this,DestroySound,GetActorLocation());
	}
	
	if(DestroyParticle != nullptr)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),DestroyParticle,GetActorTransform(),true);
	}

	ACubeRunningGameMode* CubeRunningGameMode = Cast<ACubeRunningGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	CubeRunningGameMode->AddLifeTime(IncreaseLifeTime);

	Destroy();
}


void ACRDrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DroneTakeoffTimeline.TickTimeline(DeltaTime);

	if(IsFollowPlayer)
	{
		FRotator DroneRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(),CashedPlayerCharacter->GetActorLocation());
		SetActorRotation(DroneRotation);
	}
}

