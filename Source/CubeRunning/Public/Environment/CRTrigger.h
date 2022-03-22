// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CRTrigger.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FPlayerOverlap, ACharacter*);

UCLASS()
class CUBERUNNING_API ACRTriger : public AActor
{
	GENERATED_BODY()


public:
	FPlayerOverlap OnPlayerOverlap;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent* TrigerBox;

	bool ISActivate = false;
	
	virtual void BeginPlay() override;

public:
	ACRTriger();

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
