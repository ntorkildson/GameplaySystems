// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ParallelGameMode.h"
#include "ParallelCharacter.h"
#include "UObject/ConstructorHelpers.h"

AParallelGameMode::AParallelGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/BP_ParallelCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
