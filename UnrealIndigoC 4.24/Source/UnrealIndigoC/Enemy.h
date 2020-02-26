// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Enemy.generated.h"

UCLASS()
class UNREALINDIGOC_API AEnemy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy();

protected:

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	//class UStaticMeshComponent* m_enemyMesh;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* m_skeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UFloatingPawnMovement* m_movementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ACameraRegion* m_cameraRegion;

	// Enemy Stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float m_combatDistance = 30.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float m_attackRate= 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float m_maxHealth = 50.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float m_score = 10.f;

	// Member variables
	float m_lastAttackTime;

	float m_currentHealth;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	ACameraRegion* GetCameraRegion() const;
	void SetCameraRegion(ACameraRegion* cameraRegion);

	float GetCombatDistance() const;
	
	UFUNCTION(BlueprintCallable)
	float GetCurrentHealth() const;

	void AttackPlayer(AActor* player);

	void FacePlayer(AActor* player);

	void RecieveDamage(float damage);
	
};
