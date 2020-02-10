// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "UnrealIndigoCGameMode.h"
#include "UnrealIndigoCCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUnrealIndigoCGameMode::AUnrealIndigoCGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
