// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "BarrelComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CUBERUNNING_API UBarrelComponent : public USceneComponent
{
	GENERATED_BODY()


protected:
	float FireRange = 999999.0f;
	float DamageAmount = 1.0f;

	USoundBase* FireSound;

	UParticleSystem* FireParticle;
public:	
	UBarrelComponent();

	UFUNCTION()
	void Shoot(FVector Start, FVector Direction, AController* Controller);

	void SetDamageAmount(float Damage){DamageAmount = Damage;}

	void SetFireSound(USoundBase* Sound){FireSound = Sound;}

	void SetFireParticle(UParticleSystem* Particle){FireParticle = Particle;}
};
