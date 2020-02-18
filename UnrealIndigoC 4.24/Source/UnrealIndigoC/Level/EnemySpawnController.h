// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <vector>
#include "EnemySpawnController.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALINDIGOC_API UEnemySpawnController : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemySpawnController();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float m_spawnRate = 3.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float m_maxSpawnDelay = 1.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int m_maxEnemiesSpawned = 3;

	int m_currentEnemies = 0;

	float m_nextSpawnTime = 0.f;

	bool m_spawning = false;

	std::vector<class AEnemySpawner*> m_enemySpawners;

	class ACameraRegion* m_cameraRegion;

	size_t m_spawnerCount = 0;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddEnemySpawn(AEnemySpawner* enemySpawner);

	void SetCameraRegion(class ACameraRegion* cameraRegion);

	void StopSpawning();

	void StartSpawning();

	void DecreaseEnemyCount();
		
};
