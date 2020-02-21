// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UnrealIndigoCGameMode.generated.h"

UCLASS(minimalapi)
class AUnrealIndigoCGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AUnrealIndigoCGameMode();

	UFUNCTION(BlueprintCallable)
	float GetCurrentTimer() const;

protected:

	TArray<class ACameraRegion*> m_cameraRegions;

	class APowerUp* m_timerPowerUp;

	void BeginPlay() override;

	void Tick(float DeltaSeconds) override;

	float m_lastTimerReset = 0.f;
	
	float m_timerMax = 10.f;
	
	float m_currentTimer;

	UFUNCTION()
	void BeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

};



