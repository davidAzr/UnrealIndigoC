// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/World.h"

#include "EnemyMovement.h"
#include "Level/CameraRegion.h"
#include "UnrealIndigoCGameMode.h"
#include "IndigoCharacter.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//m_enemyMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	//SetRootComponent(m_enemyMesh);
	m_skeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Skeletal Mesh");
	SetRootComponent(m_skeletalMesh);
	
	m_movementComponent = CreateDefaultSubobject<UEnemyMovement>("Movement Component");
	m_currentHealth = m_maxHealth;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	//m_enemyMesh->SetNotifyRigidBodyCollision(true);
	m_skeletalMesh->SetNotifyRigidBodyCollision(true);
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

void AEnemy::SetCameraRegion(ACameraRegion * cameraRegion)
{
	m_cameraRegion = cameraRegion;
}

float AEnemy::GetCombatDistance() const
{
	return m_combatDistance;
}

float AEnemy::GetCurrentHealth() const
{
	return m_currentHealth;
}

void AEnemy::AttackPlayer(AActor* player)
{
	auto currentTime = GetWorld()->GetTimeSeconds();
	if (currentTime - m_lastAttackTime >= m_attackRate) {
		UE_LOG(LogTemp, Warning, TEXT("Attacking player"));
		m_lastAttackTime = currentTime;
		dynamic_cast<AIndigoCharacter*>(player)->RecieveDamage(25.f);
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

void AEnemy::RecieveDamage(float damage)
{
	m_currentHealth -= damage;
	if (m_currentHealth <= 0) {
		Destroy();
		AUnrealIndigoCGameMode * mymode = Cast<AUnrealIndigoCGameMode>(GetWorld()->GetAuthGameMode());
		mymode->AddScoreToPlayer(m_score);
		if (m_cameraRegion)
			m_cameraRegion->DecreaseEnemyCount();

	}
}

