// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "Level/CameraRegion.h"
#include "Components/BoxComponent.h"
#include "Enemy.h"
#include "Engine/World.h"
#include "Level/EnemySpawnController.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_collisionBox = CreateDefaultSubobject<UBoxComponent>("Collision Box");


	static ConstructorHelpers::FClassFinder<AEnemy> ClassFinder(TEXT("Blueprint'/Game/IndigoGame/Enemies/BP_Enemy.BP_Enemy_C'"));
	if (ClassFinder.Class)
		m_enemyClassToSpawn = ClassFinder.Class;
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	if (m_cameraRegion) {
		m_cameraRegion->AddSpawnToController(this);
	}
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemySpawner::SpawnEnemy()
{
	auto enemySpawned = GetWorld()->SpawnActor<AEnemy>(m_enemyClassToSpawn, m_collisionBox->GetComponentLocation(), m_collisionBox->GetComponentRotation(), FActorSpawnParameters());
	enemySpawned->SetCameraRegion(m_cameraRegion);
}

