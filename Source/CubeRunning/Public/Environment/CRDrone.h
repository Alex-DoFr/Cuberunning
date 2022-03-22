// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CRTrigger.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "CRDrone.generated.h"

UCLASS()
class CUBERUNNING_API ACRDrone : public AActor
{
	GENERATED_BODY()

	
public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Triger")
	ACRTriger* Triger;
	
protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Meshes")
	USkeletalMeshComponent* DroneBody;
	
	bool IsFollowPlayer = false;

	bool IsActivate = false;

	TWeakObjectPtr<ACharacter> CashedPlayerCharacter;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Sounds")
	USoundBase* ActivateSound;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Sounds")
	USoundBase* DestroySound;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Effects")
	UParticleSystem* DestroyParticle;
	
	FVector StartLocation;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, meta=(MakeEditWidget), Category="Takeoff")
	FVector EndLocation;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category="Takeoff")
	UCurveFloat* DroneTakeoffCurve;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Bonuses")
	int32 IncreaseLifeTime = 10;
	
	FTimeline DroneTakeoffTimeline;
	
	virtual void BeginPlay() override;

	virtual void Activate();

	UFUNCTION()
	virtual void TransitionToBatleState();

	UFUNCTION()
	void MoveDrone(float Value);

	UFUNCTION()
	virtual void OnCalled(ACharacter* PlayerCharacter);

	UFUNCTION()
	void OnTakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	ACRDrone();
};
