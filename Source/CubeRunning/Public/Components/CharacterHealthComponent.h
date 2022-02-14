// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterHealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CUBERUNNING_API UCharacterHealthComponent : public UActorComponent
{
	GENERATED_BODY()
protected:
	TWeakObjectPtr<class ACubeRunningCharacter> CachedCharacterOwner;

	bool bIsDeath = false;

	FVector SpawnLocation;

	FRotator SpawnRotation;

	FTimerHandle RespawnTimerHandle;
public:	
	// Sets default values for this component's properties
	UCharacterHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	void Death();

	void Respawn();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
