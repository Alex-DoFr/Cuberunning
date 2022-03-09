// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayUW.generated.h"

/**
 * 
 */
UCLASS()
class CUBERUNNING_API UGameplayUW : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta=(BindWidget))
	class UImage* AimImage;
	
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* LifeTimeText;
};
