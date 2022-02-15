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
	// Weak reference to the gun owner
	TWeakObjectPtr<class ACubeRunningCharacter> CachedCharacterOwner;

	bool bIsDeath = false;

	// Location recorded at the start of the game
	FVector SpawnLocation;

	// Rotation recorded at the start of the game
	FRotator SpawnRotation;

	FTimerHandle RespawnTimerHandle;

	// Screen fade-out time at death
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Effects | VisualEffects")
	float TimeCameraFade;

	// Time to restore the color of the camera when it is restored
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Effects | VisualEffects")
	float TimeCameraUnfade; 
	
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	void Death();

	void Respawn();

public:
	UCharacterHealthComponent();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
