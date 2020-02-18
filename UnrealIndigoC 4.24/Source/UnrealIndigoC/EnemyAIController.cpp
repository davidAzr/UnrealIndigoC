// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAIController.h"
#include "Level/CameraRegion.h"
#include "Enemy.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

AEnemyAIController::AEnemyAIController() {
	SetActorTickEnabled(true);
	m_chasing = false;
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	m_enemyControlled = dynamic_cast<AEnemy*>(GetPawn());
	m_playerActor = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void AEnemyAIController::Tick(float deltaSeconds)
{
	// TODO: The methon now checks for distance manually instead of using
	// acceptance radius from MoveTo. Investigate
	Super::Tick(deltaSeconds);
	if (m_enemyControlled && m_playerActor) {
		if (m_enemyControlled->GetCameraRegion() && m_enemyControlled->GetCameraRegion()->GetIsActiveCameraRegion()) {
			auto distanceToPlayer = m_enemyControlled->GetDistanceTo(m_playerActor);
			//UE_LOG(LogTemp, Warning, TEXT("%f"), distanceToPlayer)
			if (!m_chasing) {
				
				if (distanceToPlayer > m_enemyControlled->GetCombatDistance()) {
					// We must start following because we are not in combat range
					MoveToActor(m_playerActor, -1.f , true, true, false);
					m_chasing = true;
					//UE_LOG(LogTemp, Warning, TEXT("Started chasing"))

				}
				else {
					// Not following because we are in combat range
					m_enemyControlled->FacePlayer(m_playerActor);
					m_enemyControlled->AttackPlayer(m_playerActor);
					//UE_LOG(LogTemp, Warning, TEXT("Attacking player"))
				}
			}
			if (m_chasing) {
				if (distanceToPlayer < m_enemyControlled->GetCombatDistance()) {
					// We must stop following because we are in combat range
					//UE_LOG(LogTemp, Warning, TEXT("Finished chasing"))
					StopMovement();
					m_chasing = false;
				}
			}
		}
		else {
			if (m_chasing) {
				StopMovement();
				m_chasing = false;
			}
		}
	}
	else {
		m_enemyControlled = dynamic_cast<AEnemy*>(GetPawn());
	}
}
