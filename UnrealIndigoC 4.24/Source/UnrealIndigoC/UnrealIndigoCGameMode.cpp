// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "UnrealIndigoCGameMode.h"
#include "UnrealIndigoCCharacter.h"
#include "UObject/ConstructorHelpers.h"

#include "EngineUtils.h"
#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"

#include "Level/CameraRegion.h"
#include "Level/PowerUp.h"
#include "IndigoCharacter.h"

AUnrealIndigoCGameMode::AUnrealIndigoCGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("Blueprint'/Game/IndigoGame/Character/BP_IndigoCharacter.BP_IndigoCharacter_C'"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AUnrealIndigoCGameMode::BeginPlay()
{
	Super::BeginPlay();
	// Add all camera regions of the level
	for (TActorIterator<ACameraRegion> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		m_cameraRegions.Push(*ActorItr);
	}

	for (TActorIterator<APowerUp> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		m_timerPowerUp = *ActorItr;
	}

	m_currentTimer = m_timerMax;

	// Binding Events
	if (m_timerPowerUp) {
		m_timerPowerUp->OnActorBeginOverlap.AddDynamic(this, &AUnrealIndigoCGameMode::BeginOverlap);	
	}
}

void AUnrealIndigoCGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	/*
	auto currentTime = GetWorld()->GetTimeSeconds();
	if (currentTime - m_lastTimerReset >= m_timerMax) {
		UGameplayStatics::OpenLevel(GetWorld(), FName("OriginalLevel"));
		m_lastTimerReset = currentTime;
	}
	*/

	m_currentTimer -= DeltaSeconds;
	if (m_currentTimer <= 0.f) {
		UGameplayStatics::OpenLevel(GetWorld(), FName("OriginalLevel"));
	}

	//UE_LOG(LogTemp, Warning, TEXT("%f"), currentTime)
}

void AUnrealIndigoCGameMode::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	auto playerActor = dynamic_cast<AIndigoCharacter*>(OtherActor);
	if (playerActor) {
		UE_LOG(LogTemp, Warning, TEXT("Player step up into timer"))
		auto nextIdx = FMath::FRandRange(0, m_cameraRegions.Num() - 1);
		OverlappedActor->SetActorLocation(m_cameraRegions[nextIdx]->GetActorLocation());
		m_lastTimerReset = GetWorld()->GetTimeSeconds();
	}
}
