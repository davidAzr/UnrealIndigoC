// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawnController.h"
#include "Level/EnemySpawner.h"
#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UEnemySpawnController::UEnemySpawnController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnemySpawnController::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Warning, TEXT("%f"), m_nextSpawnTime)
	// ...
	
}


// Called every frame
void UEnemySpawnController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (m_spawning) {
		auto currentTime = GetWorld()->GetTimeSeconds();
		if (m_currentEnemies < m_maxEnemiesSpawned && m_nextSpawnTime - currentTime < 0 && m_enemySpawners.size() > 0) {
			auto spawnerIndex = FMath::RandRange(0, m_enemySpawners.size() - 1);
			m_enemySpawners.at(spawnerIndex)->SpawnEnemy();
			++m_currentEnemies;
			// Calculate next spawn time
			m_nextSpawnTime = currentTime + FMath::RandRange(m_spawnRate - m_maxSpawnDelay / 2, m_spawnRate + m_maxSpawnDelay / 2);
		}
	}

}

void UEnemySpawnController::AddEnemySpawn(AEnemySpawner * enemySpawner)
{
	m_enemySpawners.push_back(enemySpawner);
	++m_spawnerCount;
}

void UEnemySpawnController::SetCameraRegion(ACameraRegion * cameraRegion)
{
	m_cameraRegion = cameraRegion;
}

void UEnemySpawnController::StopSpawning()
{
	m_spawning = false;
}

void UEnemySpawnController::StartSpawning()
{
	m_nextSpawnTime = GetWorld()->GetTimeSeconds() + FMath::RandRange(m_spawnRate - m_maxSpawnDelay / 2, m_spawnRate + m_maxSpawnDelay / 2);
	m_spawning = true;
}

void UEnemySpawnController::DecreaseEnemyCount()
{
	--m_currentEnemies;
}

