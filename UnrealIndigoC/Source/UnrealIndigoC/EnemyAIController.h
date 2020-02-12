// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALINDIGOC_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

protected:
	AEnemyAIController();

	class AEnemy* m_enemyControlled;
	
	virtual void BeginPlay() override;

public:
	virtual void Tick(float deltaSeconds) override;
	
};
