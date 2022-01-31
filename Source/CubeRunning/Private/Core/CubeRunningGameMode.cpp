// Copyright Epic Games, Inc. All Rights Reserved.

#include "Core/CubeRunningGameMode.h"
#include "HUD/CubeRunningHUD.h"
#include "Character/CubeRunningCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACubeRunningGameMode::ACubeRunningGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ACubeRunningHUD::StaticClass();
}
