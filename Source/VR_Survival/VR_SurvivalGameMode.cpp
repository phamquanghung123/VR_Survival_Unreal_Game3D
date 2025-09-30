// Copyright Epic Games, Inc. All Rights Reserved.

#include "VR_SurvivalGameMode.h"
#include "VR_SurvivalCharacter.h"
#include "UObject/ConstructorHelpers.h"

AVR_SurvivalGameMode::AVR_SurvivalGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
