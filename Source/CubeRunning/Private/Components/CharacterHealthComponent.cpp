// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CharacterHealthComponent.h"
#include "Character/CubeRunningCharacter.h"
#include "GameFramework/GameSession.h"


UCharacterHealthComponent::UCharacterHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCharacterHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	checkf(GetOwner()->IsA<ACubeRunningCharacter>(),TEXT("UCharacterHealthComponent::BeginPlay() can de used only with CubeRunningCharacter"));
	CachedCharacterOwner = StaticCast<ACubeRunningCharacter*>(GetOwner());
	CachedCharacterOwner->OnTakeAnyDamage.AddDynamic(this,&UCharacterHealthComponent::OnTakeAnyDamage);
	SpawnLocation = CachedCharacterOwner->GetActorLocation();
	SpawnRotation = CachedCharacterOwner->GetController()->GetControlRotation();
}

void UCharacterHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if(bIsDeath)
	{
		return;
	}
	Death();
}

void UCharacterHealthComponent::Death()
{
	bIsDeath = true;
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	CachedCharacterOwner->DisableInput(PlayerController);
	PlayerController->PlayerCameraManager->StartCameraFade(0.0f,1.0f,TimeCameraFade,FLinearColor::Black,false, true);
	GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle,this,&UCharacterHealthComponent::Respawn,3.0f);
}

void UCharacterHealthComponent::Respawn()
{
	if(!bIsDeath)
	{
		return;
	}
	bIsDeath = false;

	CachedCharacterOwner->SetActorLocation(SpawnLocation);
	CachedCharacterOwner->GetController()->SetControlRotation(SpawnRotation);
	
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	CachedCharacterOwner->EnableInput(PlayerController);
	PlayerController->PlayerCameraManager->StartCameraFade(1.0f,0.0f,TimeCameraUnfade,FLinearColor::Black,false, false);
}

void UCharacterHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

