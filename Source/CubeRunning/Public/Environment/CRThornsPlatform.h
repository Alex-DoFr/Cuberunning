// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Environment/CRPlatform.h"
#include "CRThornsPlatform.generated.h"

/**
 * 
 */
UCLASS()
class CUBERUNNING_API ACRThornsPlatform : public ACRplatform
{
	GENERATED_BODY()
	
	
protected:
	UPROPERTY(VisibleDefaultsOnly,BlueprintReadOnly,Category="Meshs")
	UStaticMeshComponent* ThornsMesh;

	UPROPERTY(VisibleDefaultsOnly,BlueprintReadOnly,Category="Triger")
	UBoxComponent* PainBox;

	void BeginPlay() override;

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
public:
	ACRThornsPlatform();
};
