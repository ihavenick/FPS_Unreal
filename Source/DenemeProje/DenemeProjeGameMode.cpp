// Copyright Epic Games, Inc. All Rights Reserved.

#include "DenemeProjeGameMode.h"
#include "DenemeProjeHUD.h"
#include "DenemeProjeCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADenemeProjeGameMode::ADenemeProjeGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Core/Player/Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ADenemeProjeHUD::StaticClass();
}
