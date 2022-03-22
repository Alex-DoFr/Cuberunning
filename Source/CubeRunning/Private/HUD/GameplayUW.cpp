// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/GameplayUW.h"

#include "Components/TextBlock.h"
#include "Core/CubeRunningGameMode.h"
#include "Kismet/GameplayStatics.h"

void UGameplayUW::OnGetLifeTime(int32 LifeTime)
{
	LifeTimeText->SetText(FText::FromString(FString::FromInt(LifeTime)));
}

void UGameplayUW::NativeConstruct()
{
	Super::NativeConstruct();

	ACubeRunningGameMode* CubeRunningGameMode = Cast<ACubeRunningGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	CubeRunningGameMode->OnUpdateLifetime.AddUFunction(this, FName("OnGetLifeTime"));
	LifeTimeText->SetText(FText::FromString(FString::FromInt(CubeRunningGameMode->GetLifeTime())));
}
