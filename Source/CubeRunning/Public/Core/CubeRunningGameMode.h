// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CubeRunningGameMode.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FUpdateLifetime,int32);

UCLASS(minimalapi)
class ACubeRunningGameMode : public AGameModeBase
{
	GENERATED_BODY()

	
protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category="Time")
	int32 LifeTime;
	
public:
	TWeakObjectPtr<class ACubeRunningCharacter> GameСharacter;
	
	FTimerHandle UpdateLifetimeTimerHandle;

	FUpdateLifetime OnUpdateLifetime;
	
	ACubeRunningGameMode();
	
	void GameСharacterDied();

	int32 GetLifeTime(){return LifeTime;}

	// Increases the LifeTime by the passed value and returns a new LifeTime. If the passed value is incorrect, it returns -1
	int32 AddLifeTime(int32 Added);
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void UpdateLifetime();

	void LevelReboot();
};



