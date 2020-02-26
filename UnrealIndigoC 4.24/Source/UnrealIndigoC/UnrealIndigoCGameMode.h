// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UnrealIndigoCGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTimerRunsOut, float, time);

UCLASS(minimalapi)
class AUnrealIndigoCGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AUnrealIndigoCGameMode();

	UFUNCTION(BlueprintCallable)
	float GetCurrentTimer() const;

	UFUNCTION(BlueprintCallable)
	float GetPlayerScore() const;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FTimerRunsOut TimeRunsOut;

	void AddScoreToPlayer(float score);


protected:

	TArray<class ACameraRegion*> m_cameraRegions;

	class APowerUp* m_timerPowerUp;

	void BeginPlay() override;

	void Tick(float DeltaSeconds) override;

	float m_lastTimerReset = 0.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration")
	float m_timerMax = 10.f;
	
	float m_currentTimer;

	float m_playerScore;

	UFUNCTION()
	void BeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

};



