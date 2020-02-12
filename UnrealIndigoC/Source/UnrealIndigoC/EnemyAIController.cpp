// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAIController.h"
#include "Level/CameraRegion.h"
#include "Enemy.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

AEnemyAIController::AEnemyAIController() {
	SetActorTickEnabled(true);
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	m_enemyControlled = dynamic_cast<AEnemy*>(GetPawn());
}

void AEnemyAIController::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);
	if (m_enemyControlled) {
		if (m_enemyControlled->GetCameraRegion()->GetIsActiveCameraRegion()) {
			MoveToActor(GetWorld()->GetFirstPlayerController()->GetPawn(), m_enemyControlled->GetCombatDistance(), true, true, false);
		}
		else {
			StopMovement();
		}
	}
}
