// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "UnrealIndigoCGameMode.h"
#include "UnrealIndigoCCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUnrealIndigoCGameMode::AUnrealIndigoCGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("Blueprint'/Game/IndigoGame/Character/BP_IndigoCharacter.BP_IndigoCharacter_C'"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}