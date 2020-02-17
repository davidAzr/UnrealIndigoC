// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"
//#include "GameFramework/FloatingPawnMovement.h"
#include "EnemyMovement.h"
#include "Components/StaticMeshComponent.h"
#include "Level/CameraRegion.h"
#include "Engine/World.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_enemyMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(m_enemyMesh);
	m_movementComponent = CreateDefaultSubobject<UEnemyMovement>("Movement Component");

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	m_enemyMesh->SetNotifyRigidBodyCollision(true);
	m_lastAttackTime = 0.f;
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

ACameraRegion* AEnemy::GetCameraRegion() const
{
	return m_cameraRegion;
}

float AEnemy::GetCombatDistance() const
{
	return m_combatDistance;
}

void AEnemy::AttackPlayer()
{
	auto currentTime = GetWorld()->GetTimeSeconds();
	if (currentTime - m_lastAttackTime >= m_attackRate) {
		UE_LOG(LogTemp, Warning, TEXT("Attacking player"));
		m_lastAttackTime = currentTime;
	}
}

void AEnemy::FacePlayer(AActor* player)
{
	auto directionToPlayer = player->GetActorLocation() - GetActorLocation();
	auto StartRot = GetActorRotation();
	auto TargetRot = (directionToPlayer * -1).Rotation();
	auto Speed = 3.f;

	SetActorRotation(FMath::RInterpTo(StartRot, TargetRot, GetWorld()->GetDeltaSeconds(), Speed));
}

