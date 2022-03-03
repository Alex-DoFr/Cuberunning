// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CRPlatform.generated.h"

UENUM()
enum class EPlatformsTupe: uint8
{
	flat,
	cruciform
};


UCLASS()
class CUBERUNNING_API ACRplatform : public AActor
{
	GENERATED_BODY()
	

protected:
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Meshs")
	EPlatformsTupe PlatformsTupe = EPlatformsTupe::flat;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category="Meshs")
	UStaticMesh* PlatformMeshFlat;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category="Meshs")
	UStaticMesh* PlatformMeshCruciform;
	
	UPROPERTY(VisibleDefaultsOnly,BlueprintReadOnly,Category="Meshs")
	UStaticMeshComponent* PlatformMesh;

	virtual void BeginPlay() override;
	
public:	
	virtual void Tick(float DeltaTime) override;

	ACRplatform();

	void OnConstruction(const FTransform& Transform) override;
};
