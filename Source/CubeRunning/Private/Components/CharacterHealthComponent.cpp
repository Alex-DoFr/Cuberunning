// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CharacterHealthComponent.h"
#include "Character/CubeRunningCharacter.h"
#include "Core/CubeRunningGameMode.h"
#include "GameFramework/GameSession.h"
#include "Kismet/GameplayStatics.h"


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
	
	CubeRunningGameMode = Cast< ACubeRunningGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	CubeRunningGameMode->GameСharacter = StaticCast<ACubeRunningCharacter*>(GetOwner());
	
	Respawn();
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
	GetWorld()->GetTimerManager().SetTimer(DeathDelayTimerHandle,this,&UCharacterHealthComponent::NotifyGameMpdOfDeath, TimeCameraFade);
}

void UCharacterHealthComponent::Respawn()
{
	if(!bIsDeath)
	{
		return;
	}
	bIsDeath = false;

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerController->PlayerCameraManager->StartCameraFade(1.0f,0.0f,TimeCameraUnfade,FLinearColor::Black,false, false);
}

void UCharacterHealthComponent::NotifyGameMpdOfDeath()
{
	CubeRunningGameMode->GameСharacterDied();
}



